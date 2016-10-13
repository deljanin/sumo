#!/usr/bin/env python
"""
@file    sikulixTestRunner.py
@date    2016-0-01
@author  Pablo Alvarez Lopez
@version $Id: sikulixTestRunner.py 20433 2016-04-13 08:00:14Z behrisch $

Wrapper script for running gui tests with SikuliX and TextTest.

SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
Copyright (C) 2008-2016 DLR (http://www.dlr.de/) and contributors

This file is part of SUMO.
SUMO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
"""
import socket
import os
import sys
import platform

# get enviroment values
SUMOFolder = os.environ.get('SUMO_HOME', '.')
neteditApp = os.environ.get('NETEDIT_BINARY', '.')
textTestSandBox = os.environ.get('TEXTTEST_SANDBOX', '.')

# Get current operating system
currentOS = platform.system()

# Write enviroment variables in currentEnvironment.tmp
file = open(SUMOFolder + "/tests/netedit/currentEnvironment.tmp", "w")
file.write(neteditApp + "\n" + textTestSandBox + "\n" + currentOS)
file.close()

# Check status of sikulix Server
statusSocket = socket.socket()
try:
    statusSocket.connect(("localhost", 50001))
    statusSocket.send("GET / HTTP/1.1\n\n")
    statusReceived = statusSocket.recv(1024)
    statusSocket.close()
    # If status of server contains "200 OK", Sikulix server is ready, in other case is ocupped
    if "200 OK" not in statusReceived:
        sys.exit("Sikulix server not ready")
except:
    # Cannot connect to SikulixServer, then Sikulix Server isn't running
    sys.exit("Sikulix server isn't running")

# IMAGES
imagesSocket = socket.socket()
imagesSocket.connect(("localhost", 50001))
imagesSocket.send("GET /images/" + SUMOFolder + "/tests/netedit/imageResources HTTP/1.1\n\n")
imagesReceived = (imagesSocket.recv(1024))
imagesSocket.close()
if "200 OK" not in imagesReceived:
    sys.exit("Error adding imageResources folder '" + SUMOFolder + "/tests/netedit/imageResources'")

# SCRIPT    
scriptSocket = socket.socket()
scriptSocket.connect(("localhost", 50001))
scriptSocket.send("GET /scripts/" + textTestSandBox + " HTTP/1.1\n\n")
scriptReceived = (scriptSocket.recv(1024))
scriptSocket.close()
if "200 OK" not in scriptReceived:
    sys.exit("Error adding script folder '" + SUMOFolder + + "/tests/netedit/" + sys.argv[1] + "'")

# RUN
runSocket = socket.socket()
runSocket.connect(("localhost", 50001))
runSocket.send("GET /run/test.sikuli HTTP/1.1\n\n")
runReceived = (runSocket.recv(1024))
runSocket.close();
if "200 OK" not in runReceived:
    sys.exit("error running 'test.sikuli' %s" % runReceived)