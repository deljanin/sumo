/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2020 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GNEApplicationWindowHelper.cpp
/// @author  Jakob Erdmann
/// @date    Feb 2011
///
// The main window of Netedit (adapted from GUIApplicationWindow)
/****************************************************************************/
#include <netbuild/NBFrame.h>
#include <utils/gui/div/GUIDesigns.h>
#include <utils/gui/windows/GUIAppEnum.h>

#include "GNEApplicationWindow.h"
#include "GNEViewNet.h"

#ifdef HAVE_VERSION_H
#include <version.h>
#endif

// ===========================================================================
// GNEApplicationWindowHelper::ToolbarsGrip method definitions
// ===========================================================================

GNEApplicationWindowHelper::ToolbarsGrip::ToolbarsGrip(GNEApplicationWindow* GNEApp) :
    menu(nullptr),
    superModes(nullptr),
    saveElements(nullptr),
    navigation(nullptr),
    modes(nullptr),
    modeOptions(nullptr),
    intervalBar(nullptr),
    myTopDock(nullptr),
    myGNEApp(GNEApp),
    myToolBarShellMenu(nullptr),
    myToolBarShellSuperModes(nullptr),
    myToolBarShellSaveElements(nullptr),
    myToolBarShellNavigation(nullptr),
    myToolBarShellModes(nullptr),
    myToolBarShellModeOptions(nullptr),
    myToolBarShellIntervalBar(nullptr) {
}


void
GNEApplicationWindowHelper::ToolbarsGrip::buildMenuToolbarsGrip() {
    // build menu bar (for File, edit, processing...) using specify design
    myToolBarShellMenu = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    menu = new FXMenuBar(myTopDock, myToolBarShellMenu, GUIDesignToolbarMenuBarNetedit);
    // declare toolbar grip for menu bar
    new FXToolBarGrip(menu, menu, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
}


void
GNEApplicationWindowHelper::ToolbarsGrip::buildViewParentToolbarsGrips() {
    // build menu bar for supermodes (next to menu bar)
    myToolBarShellSuperModes = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    superModes = new FXMenuBar(myTopDock, myToolBarShellSuperModes, GUIDesignToolBarRaisedSame);
    // declare toolbar grip for menu bar superModes
    new FXToolBarGrip(superModes, superModes, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
    // build menu bar for save elements (bot to menu bar)
    myToolBarShellSaveElements = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    saveElements = new FXMenuBar(myTopDock, myToolBarShellSaveElements, GUIDesignToolBarRaisedNext);
    // declare toolbar grip for menu bar saveElements
    new FXToolBarGrip(saveElements, saveElements, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
    // build menu bar for navigation
    myToolBarShellNavigation = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    navigation = new FXMenuBar(myTopDock, myToolBarShellNavigation, GUIDesignToolBarRaisedSame);
    // declare toolbar grip for menu bar navigation
    new FXToolBarGrip(navigation, navigation, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
    // build menu bar for modes
    myToolBarShellModes = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    modes = new FXMenuBar(myTopDock, myToolBarShellModes, GUIDesignToolBarRaisedSame);
    // declare toolbar grip for menu bar modes
    new FXToolBarGrip(modes, modes, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
    // build menu bar for mode Options
    myToolBarShellModeOptions = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    modeOptions = new FXMenuBar(myTopDock, myToolBarShellModeOptions, GUIDesignToolBarRaisedSame);
    // declare toolbar grip for menu bar modes
    new FXToolBarGrip(modeOptions, modeOptions, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
    // build menu bar for interal
    myToolBarShellIntervalBar = new FXToolBarShell(myGNEApp, GUIDesignToolBar);
    intervalBar = new FXMenuBar(myTopDock, myToolBarShellModeOptions, GUIDesignToolBarRaisedNext);
    // declare toolbar grip for menu bar modes
    new FXToolBarGrip(intervalBar, intervalBar, FXMenuBar::ID_TOOLBARGRIP, GUIDesignToolBarGrip);
    // create menu bars
    superModes->create();
    saveElements->create();
    navigation->create();
    modes->create();
    modeOptions->create();
    intervalBar->create();
    // create toolbar shells
    myToolBarShellSuperModes->create();
    myToolBarShellSaveElements->create();
    myToolBarShellNavigation->create();
    myToolBarShellModes->create();
    myToolBarShellModeOptions->create();
    myToolBarShellIntervalBar->create();
    // recalc top dop after creating elements
    myTopDock->recalc();
}


void
GNEApplicationWindowHelper::ToolbarsGrip::destroyParentToolbarsGrips() {
    // delete Menu bars
    delete superModes;
    delete saveElements;
    delete navigation;
    delete modes;
    delete modeOptions;
    delete intervalBar;
    // also delete toolbar shells to avoid floating windows
    delete myToolBarShellSuperModes;
    delete myToolBarShellSaveElements;
    delete myToolBarShellNavigation;
    delete myToolBarShellModes;
    delete myToolBarShellModeOptions;
    delete myToolBarShellIntervalBar;
    // recalc top dop after deleting elements
    myTopDock->recalc();
}

// ===========================================================================
// GNEApplicationWindowHelper::MenuBarFile method definitions
// ===========================================================================

GNEApplicationWindowHelper::MenuBarFile::MenuBarFile(GNEApplicationWindow* GNEApp) :
    myRecentNets(GNEApp->getApp(), "nets"),
    myGNEApp(GNEApp)
{ }


void
GNEApplicationWindowHelper::MenuBarFile::buildRecentFiles(FXMenuPane* fileMenu) {
    FXMenuSeparator* sep1 = new FXMenuSeparator(fileMenu);
    sep1->setTarget(&myRecentConfigs);
    sep1->setSelector(FXRecentFiles::ID_ANYFILES);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_1);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_2);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_3);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_4);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_5);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_6);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_7);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_8);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_9);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentConfigs, FXRecentFiles::ID_FILE_10);
    GUIDesigns::buildFXMenuCommand(fileMenu, "Clear Recent Configurat&ions", nullptr, &myRecentConfigs, FXRecentFiles::ID_CLEAR);
    myRecentConfigs.setTarget(myGNEApp);
    myRecentConfigs.setSelector(MID_RECENTFILE);
    FXMenuSeparator* sep2 = new FXMenuSeparator(fileMenu);
    sep2->setTarget(&myRecentNets);
    sep2->setSelector(FXRecentFiles::ID_ANYFILES);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_1);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_2);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_3);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_4);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_5);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_6);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_7);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_8);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_9);
    GUIDesigns::buildFXMenuCommand(fileMenu, "", nullptr, &myRecentNets, FXRecentFiles::ID_FILE_10);
    GUIDesigns::buildFXMenuCommand(fileMenu, "Cl&ear Recent Networks\t\tClear the list of recently used networks.", nullptr, &myRecentNets, FXRecentFiles::ID_CLEAR);
    myRecentNets.setTarget(myGNEApp);
    myRecentNets.setSelector(MID_RECENTFILE);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::FileMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::FileMenuCommands::FileMenuCommands(GNEApplicationWindow* GNEApp) :
    saveAdditionals(nullptr),
    saveAdditionalsAs(nullptr),
    saveTLSPrograms(nullptr),
    saveDemandElements(nullptr),
    saveDemandElementsAs(nullptr),
    saveDataElements(nullptr),
    saveDataElementsAs(nullptr),
    myGNEApp(GNEApp) {
}


void
GNEApplicationWindowHelper::FileMenuCommands::buildFileMenuCommands(FXMenuPane* fileMenu, FXMenuPane* fileMenuTLS, FXMenuPane* fileMenuAdditionals,
        FXMenuPane* fileMenuDemandElements, FXMenuPane* fileMenuDataElements) {
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "&New Network\tCtrl+N\tCreate a new network.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_NET), myGNEApp, MID_HOTKEY_CTRL_N_NEWNETWORK);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "&Open Network...\tCtrl+O\tOpen a SUMO network.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_NET), myGNEApp, MID_OPEN_NETWORK);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "Open Netconvert Configura&tion...\tCtrl+Shift+O\tOpen a configuration file with NETCONVERT options.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_CONFIG), myGNEApp, MID_OPEN_CONFIG);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "Import &Foreign Network...\t\tImport a foreign network such as OSM.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_NET), myGNEApp, MID_GNE_TOOLBARFILE_OPENFOREIGN);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "&Reload\tCtrl+R\tReload the network.",
                      GUIIconSubSys::getIcon(GUIIcon::RELOAD), myGNEApp, MID_HOTKEY_CTRL_R_RELOAD);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "&Save Network\tCtrl+S\tSave the network.",
                      GUIIconSubSys::getIcon(GUIIcon::SAVE), myGNEApp, MID_HOTKEY_CTRL_S_STOPSIMULATION_SAVENETWORK);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "Save Net&work As...\tCtrl+Shift+S\tSave the network to another file.",
                      GUIIconSubSys::getIcon(GUIIcon::SAVE), myGNEApp, MID_HOTKEY_CTRL_SHIFT_S_SAVENETWORK_AS);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "Save Plain XM&L...\tCtrl+L\tSave plain XML representation the network.",
                      GUIIconSubSys::getIcon(GUIIcon::SAVE), myGNEApp, MID_HOTKEY_CTRL_L_SAVEASPLAINXML);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "Save &Joined Junctions...\tCtrl+J\tSave log of joined junctions (allows reproduction of joins).",
                      GUIIconSubSys::getIcon(GUIIcon::SAVE), myGNEApp, MID_HOTKEY_CTRL_J_SAVEJOINEDJUNCTIONS);
    // create TLS menu options
    GUIDesigns::buildFXMenuCommand(fileMenuTLS,
                      "Load TLS Programs...\tCtrl+K\tLoad programs for traffic lights in the current net.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_TLSPROGRAMS), myGNEApp, MID_HOTKEY_CTRL_K_OPENTLSPROGRAMS);
    saveTLSPrograms = GUIDesigns::buildFXMenuCommand(fileMenuTLS,
                                        "Save TLS Programs\tCtrl+Shift+K\tSave all traffic light programs of the current net.",
                                        GUIIconSubSys::getIcon(GUIIcon::SAVE), myGNEApp, MID_HOTKEY_CTRL_SHIFT_K_SAVETLS);
    saveTLSPrograms->disable();
    GUIDesigns::buildFXMenuCommand(fileMenuTLS,
                      "Save TLS Programs As...\t\tSave all traffic light programs of the current net to another file.",
                      GUIIconSubSys::getIcon(GUIIcon::SAVE), myGNEApp, MID_GNE_TOOLBARFILE_SAVETLSPROGRAMS_AS);
    new FXMenuCascade(fileMenu,
                      "Traffic Lights",
                      GUIIconSubSys::getIcon(GUIIcon::MODETLS), fileMenuTLS);
    // create Additionals menu options
    GUIDesigns::buildFXMenuCommand(fileMenuAdditionals,
                      "Load A&dditionals...\tCtrl+A\tLoad additionals and shapes.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_ADDITIONALS), myGNEApp, MID_HOTKEY_CTRL_A_STARTSIMULATION_OPENADDITIONALS);
    saveAdditionals = GUIDesigns::buildFXMenuCommand(fileMenuAdditionals,
                                        "Save Additionals\tCtrl+Shift+A\tSave additionals and shapes.",
                                        GUIIconSubSys::getIcon(GUIIcon::SAVEADDITIONALELEMENTS), myGNEApp, MID_HOTKEY_CTRL_SHIFT_A_SAVEADDITIONALS);
    saveAdditionals->disable();
    saveAdditionalsAs = GUIDesigns::buildFXMenuCommand(fileMenuAdditionals,
                                          "Save Additionals As...\t\tSave additional elements to another file.",
                                          GUIIconSubSys::getIcon(GUIIcon::SAVEADDITIONALELEMENTS), myGNEApp, MID_GNE_TOOLBARFILE_SAVEADDITIONALS_AS);
    saveAdditionalsAs->disable();
    new FXMenuCascade(fileMenu, "Additionals and shapes", GUIIconSubSys::getIcon(GUIIcon::MODEADDITIONAL), fileMenuAdditionals);
    // create DemandElements menu options
    GUIDesigns::buildFXMenuCommand(fileMenuDemandElements,
                      "Load Demand Elements...\tCtrl+D\tLoad demand elements.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_ADDITIONALS), myGNEApp, MID_HOTKEY_CTRL_D_SINGLESIMULATIONSTEP_OPENDEMANDELEMENTS);
    saveDemandElements = GUIDesigns::buildFXMenuCommand(fileMenuDemandElements,
                                           "Save Demand Elements\tCtrl+Shift+D\tSave demand elements.",
                                           GUIIconSubSys::getIcon(GUIIcon::SAVEDEMANDELEMENTS), myGNEApp, MID_HOTKEY_CTRL_SHIFT_D_SAVEDEMANDELEMENTS);
    saveDemandElements->disable();
    saveDemandElementsAs = GUIDesigns::buildFXMenuCommand(fileMenuDemandElements,
            "Save Demand Elements As...\t\tSave demand elements to another file.",
            GUIIconSubSys::getIcon(GUIIcon::SAVEDEMANDELEMENTS), myGNEApp, MID_GNE_TOOLBARFILE_SAVEDEMAND_AS);
    saveDemandElementsAs->disable();
    new FXMenuCascade(fileMenu,
                      "Demand Elements",
                      GUIIconSubSys::getIcon(GUIIcon::SUPERMODEDEMAND), fileMenuDemandElements);
    // create DataElements menu options
    GUIDesigns::buildFXMenuCommand(fileMenuDataElements,
                      "Load Data Wlements...\tCtrl+B\tLoad data elements.",
                      GUIIconSubSys::getIcon(GUIIcon::OPEN_ADDITIONALS), myGNEApp, MID_HOTKEY_CTRL_B_EDITBREAKPOINT_OPENDATAELEMENTS);
    saveDataElements = GUIDesigns::buildFXMenuCommand(fileMenuDataElements,
                                         "Save Data Elements\tCtrl+Shift+B\tSave data elements.",
                                         GUIIconSubSys::getIcon(GUIIcon::SAVEDATAELEMENTS), myGNEApp, MID_HOTKEY_CTRL_SHIFT_B_SAVEDATAELEMENTS);
    saveDataElements->disable();
    saveDataElementsAs = GUIDesigns::buildFXMenuCommand(fileMenuDataElements,
                                           "Save Data Elements As...\t\tSave data elements to another file.",
                                           GUIIconSubSys::getIcon(GUIIcon::SAVEDATAELEMENTS), myGNEApp, MID_GNE_TOOLBARFILE_SAVEDATA_AS);
    saveDataElementsAs->disable();
    new FXMenuCascade(fileMenu,
                      "Data Elements",
                      GUIIconSubSys::getIcon(GUIIcon::SUPERMODEDATA), fileMenuDataElements);
    // close network
    new FXMenuSeparator(fileMenu);
    GUIDesigns::buildFXMenuCommand(fileMenu,
                      "Close\tCtrl+W\tClose the network.",
                      GUIIconSubSys::getIcon(GUIIcon::CLOSE), myGNEApp, MID_HOTKEY_CTRL_W_CLOSESIMULATION);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::EditMenuCommands::NetworkMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::EditMenuCommands::NetworkMenuCommands::NetworkMenuCommands(const EditMenuCommands* editMenuCommandsParent) :
    createEdgeMode(nullptr),
    moveMode(nullptr),
    deleteMode(nullptr),
    inspectMode(nullptr),
    selectMode(nullptr),
    connectMode(nullptr),
    prohibitionMode(nullptr),
    TLSMode(nullptr),
    additionalMode(nullptr),
    crossingMode(nullptr),
    TAZMode(nullptr),
    shapeMode(nullptr),
    myEditMenuCommandsParent(editMenuCommandsParent),
    myHorizontalSeparator(nullptr) {
}


void
GNEApplicationWindowHelper::EditMenuCommands::NetworkMenuCommands::showNetworkMenuCommands() {
    createEdgeMode->show();
    moveMode->show();
    deleteMode->show();
    inspectMode->show();
    selectMode->show();
    connectMode->show();
    prohibitionMode->show();
    TLSMode->show();
    additionalMode->show();
    crossingMode->show();
    TAZMode->show();
    shapeMode->show();
    // also show separator
    myHorizontalSeparator->show();
}


void
GNEApplicationWindowHelper::EditMenuCommands::NetworkMenuCommands::hideNetworkMenuCommands() {
    createEdgeMode->hide();
    moveMode->hide();
    deleteMode->hide();
    inspectMode->hide();
    selectMode->hide();
    connectMode->hide();
    prohibitionMode->hide();
    TLSMode->hide();
    additionalMode->hide();
    crossingMode->hide();
    TAZMode->hide();
    shapeMode->hide();
    // also hide separator
    myHorizontalSeparator->hide();
}


void
GNEApplicationWindowHelper::EditMenuCommands::NetworkMenuCommands::buildNetworkMenuCommands(FXMenuPane* editMenu) {
    // build every FXMenuCommand giving it a shortcut
    createEdgeMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                       "&Edge mode\tE\tCreate junction and edges.",
                                       GUIIconSubSys::getIcon(GUIIcon::MODECREATEEDGE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_E_MODES_EDGE_EDGEDATA);
    moveMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                 "&Move mode\tM\tMove elements.",
                                 GUIIconSubSys::getIcon(GUIIcon::MODEMOVE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_M_MODES_MOVE);
    deleteMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                   "&Delete mode\tD\tDelete elements.",
                                   GUIIconSubSys::getIcon(GUIIcon::MODEDELETE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_D_MODES_DELETE);
    inspectMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                    "&Inspect mode\tI\tInspect elements and change their attributes.",
                                    GUIIconSubSys::getIcon(GUIIcon::MODEINSPECT), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_I_MODES_INSPECT);
    selectMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                   "&Select mode\tS\tSelect elements.",
                                   GUIIconSubSys::getIcon(GUIIcon::MODESELECT), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_S_MODES_SELECT);
    connectMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                    "&Connection mode\tC\tEdit connections between lanes.",
                                    GUIIconSubSys::getIcon(GUIIcon::MODECONNECTION), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_C_MODES_CONNECT_PERSONPLAN);
    prohibitionMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                        "Pro&hibition mode\tW\tEdit connection prohibitions.",
                                        GUIIconSubSys::getIcon(GUIIcon::MODEPROHIBITION), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_W_MODES_PROHIBITION_PERSONTYPE);
    TLSMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                "&Traffic light mode\tT\tEdit traffic lights over junctions.",
                                GUIIconSubSys::getIcon(GUIIcon::MODETLS), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_T_MODES_TLS_VTYPE);
    additionalMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                       "&Additional mode\tA\tCreate additional elements.",
                                       GUIIconSubSys::getIcon(GUIIcon::MODEADDITIONAL), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_A_MODES_ADDITIONAL_STOP);
    crossingMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                     "C&rossing mode\tR\tCreate crossings between edges.",
                                     GUIIconSubSys::getIcon(GUIIcon::MODECROSSING), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_R_MODES_CROSSING_ROUTE_EDGERELDATA);
    TAZMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                "TA&Z mode\tZ\tCreate Traffic Assignment Zones.",
                                GUIIconSubSys::getIcon(GUIIcon::MODETAZ), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_Z_MODES_TAZ_TAZREL);
    shapeMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                  "&POI-Poly mode\tP\tCreate Points-Of-Interest and polygons.",
                                  GUIIconSubSys::getIcon(GUIIcon::MODEPOLYGON), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_P_MODES_POLYGON_PERSON);
    // build separator
    myHorizontalSeparator = new FXMenuSeparator(editMenu);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::EditMenuCommands::DemandMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::EditMenuCommands::DemandMenuCommands::DemandMenuCommands(const EditMenuCommands* editMenuCommandsParent) :
    routeMode(nullptr),
    vehicleMode(nullptr),
    vehicleTypeMode(nullptr),
    stopMode(nullptr),
    personTypeMode(nullptr),
    personMode(nullptr),
    personPlanMode(nullptr),
    myEditMenuCommandsParent(editMenuCommandsParent),
    myHorizontalSeparator(nullptr) {
}


void
GNEApplicationWindowHelper::EditMenuCommands::DemandMenuCommands::showDemandMenuCommands() {
    routeMode->show();
    vehicleMode->show();
    vehicleTypeMode->show();
    stopMode->show();
    personTypeMode->show();
    personMode->show();
    personPlanMode->show();
    // also show separator
    myHorizontalSeparator->show();
}


void
GNEApplicationWindowHelper::EditMenuCommands::DemandMenuCommands::hideDemandMenuCommands() {
    routeMode->hide();
    vehicleMode->hide();
    vehicleTypeMode->hide();
    stopMode->hide();
    personTypeMode->hide();
    personMode->hide();
    personPlanMode->hide();
    // also hide separator
    myHorizontalSeparator->hide();
}


void
GNEApplicationWindowHelper::EditMenuCommands::DemandMenuCommands::buildDemandMenuCommands(FXMenuPane* editMenu) {
    // build every FXMenuCommand giving it a shortcut
    routeMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                  "Route mode\tR\tCreate Routes.",
                                  GUIIconSubSys::getIcon(GUIIcon::MODEROUTE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_R_MODES_CROSSING_ROUTE_EDGERELDATA);
    vehicleMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                    "Vehicle mode\tV\tCreate vehicles.",
                                    GUIIconSubSys::getIcon(GUIIcon::MODEVEHICLE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_V_MODES_VEHICLE);
    vehicleTypeMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                        "Vehicle type mode\tT\tCreate vehicle types.",
                                        GUIIconSubSys::getIcon(GUIIcon::MODEVEHICLETYPE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_T_MODES_TLS_VTYPE);
    stopMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                 "Stop mode\tA\tCreate stops.",
                                 GUIIconSubSys::getIcon(GUIIcon::MODESTOP), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_A_MODES_ADDITIONAL_STOP);
    personTypeMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                       "Person type mode\tW\tCreate person types.",
                                       GUIIconSubSys::getIcon(GUIIcon::MODEPERSONTYPE), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_W_MODES_PROHIBITION_PERSONTYPE);
    personMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                   "Person mode\tP\tCreate persons.",
                                   GUIIconSubSys::getIcon(GUIIcon::MODEPERSON), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_P_MODES_POLYGON_PERSON);
    personPlanMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                       "Person plan mode\tC\tCreate person plans.",
                                       GUIIconSubSys::getIcon(GUIIcon::MODEPERSONPLAN), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_C_MODES_CONNECT_PERSONPLAN);
    // build separator
    myHorizontalSeparator = new FXMenuSeparator(editMenu);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::EditMenuCommands::DataMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::EditMenuCommands::DataMenuCommands::DataMenuCommands(const EditMenuCommands* editMenuCommandsParent) :
    edgeData(nullptr),
    edgeRelData(nullptr),
    TAZRelData(nullptr),
    myEditMenuCommandsParent(editMenuCommandsParent),
    myHorizontalSeparator(nullptr) {
}


void
GNEApplicationWindowHelper::EditMenuCommands::DataMenuCommands::showDataMenuCommands() {
    edgeData->show();
    edgeRelData->show();
    TAZRelData->show();
    // also show separator
    myHorizontalSeparator->show();
}


void
GNEApplicationWindowHelper::EditMenuCommands::DataMenuCommands::hideDataMenuCommands() {
    edgeData->hide();
    edgeRelData->hide();
    TAZRelData->hide();
    // also hide separator
    myHorizontalSeparator->hide();
}


void
GNEApplicationWindowHelper::EditMenuCommands::DataMenuCommands::buildDataMenuCommands(FXMenuPane* editMenu) {
    // build every FXMenuCommand giving it a shortcut
    edgeData = GUIDesigns::buildFXMenuCommand(editMenu,
                                 "EdgeData Mode\tE\tCreate edgeData elements.",
                                 GUIIconSubSys::getIcon(GUIIcon::MODEEDGEDATA), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_E_MODES_EDGE_EDGEDATA);
    edgeRelData = GUIDesigns::buildFXMenuCommand(editMenu,
                                    "EdgeRelation Mode\tR\tCreate edgeRelation elements.",
                                    GUIIconSubSys::getIcon(GUIIcon::MODEEDGERELDATA), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_R_MODES_CROSSING_ROUTE_EDGERELDATA);
    TAZRelData = GUIDesigns::buildFXMenuCommand(editMenu,
                                   "TAZRelation Mode\tR\tCreate TAZRelation elements.",
                                   GUIIconSubSys::getIcon(GUIIcon::MODETAZRELDATA), myEditMenuCommandsParent->myGNEApp, MID_HOTKEY_Z_MODES_TAZ_TAZREL);
    // build separator
    myHorizontalSeparator = new FXMenuSeparator(editMenu);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::EditMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::EditMenuCommands::EditMenuCommands(GNEApplicationWindow* GNEApp) :
    myGNEApp(GNEApp),
    networkMenuCommands(this),
    demandMenuCommands(this),
    dataMenuCommands(this),
    undoLastChange(nullptr),
    redoLastChange(nullptr),
    editViewScheme(nullptr),
    editViewPort(nullptr),
    toogleGrid(nullptr),
    clearFrontElement(nullptr),
    loadAdditionalsInSUMOGUI(nullptr),
    loadDemandInSUMOGUI(nullptr),
    openInSUMOGUI(nullptr) {
}


void
GNEApplicationWindowHelper::EditMenuCommands::buildEditMenuCommands(FXMenuPane* editMenu) {
    // build Network modes commands and hide it
    networkMenuCommands.buildNetworkMenuCommands(editMenu);
    networkMenuCommands.hideNetworkMenuCommands();
    // build Demand Modes commands
    demandMenuCommands.buildDemandMenuCommands(editMenu);
    demandMenuCommands.hideDemandMenuCommands();
    // build Data Modes commands
    dataMenuCommands.buildDataMenuCommands(editMenu);
    dataMenuCommands.hideDataMenuCommands();
    // build rest of menu commands
    editViewScheme = GUIDesigns::buildFXMenuCommand(editMenu,
                                       "Edit Visualisation\tF9\tOpens a dialog for editing visualization settings.",
                                       GUIIconSubSys::getIcon(GUIIcon::COLORWHEEL), myGNEApp, MID_HOTKEY_F9_EDIT_VIEWSCHEME);
    editViewScheme->setWidth(23);
    editViewScheme->setHeight(23);
    editViewPort = GUIDesigns::buildFXMenuCommand(editMenu,
                                     "Edit Viewport\tCtrl+I\tOpens a dialog for editing viewing are, zoom and rotation.",
                                     GUIIconSubSys::getIcon(GUIIcon::EDITVIEWPORT), myGNEApp, MID_HOTKEY_CTRL_I_EDITVIEWPORT);
    toogleGrid = GUIDesigns::buildFXMenuCommand(editMenu,
                                   "Toggle Grid\tCtrl+G\tToggles background grid (and snap-to-grid functionality).",
                                    GUIIconSubSys::getIcon(GUIIcon::GRID), myGNEApp, MID_HOTKEY_CTRL_G_GAMINGMODE_TOOGLEGRID);
    // add separator
    new FXMenuSeparator(editMenu);
    // add clear front element
    clearFrontElement = GUIDesigns::buildFXMenuCommand(editMenu,
                                          "Clear front element\tF11\tClear current front element",
                                          GUIIconSubSys::getIcon(GUIIcon::FRONTELEMENT), myGNEApp, MID_HOTKEY_F11_FRONTELEMENT);
    // add separator
    new FXMenuSeparator(editMenu);
    // add open in sumo options
    loadAdditionalsInSUMOGUI = new FXMenuCheck(editMenu,
        "Load additionals in sumo-gui\t\tLoad additionals in sumo-gui.",
        myGNEApp, MID_GNE_TOOLBAREDIT_LOADADDITIONALS);
    loadAdditionalsInSUMOGUI->setCheck(TRUE);
    loadDemandInSUMOGUI = new FXMenuCheck(editMenu,
        "Load demand in sumo-gui\t\tLoad demand in sumo-gui.",
        myGNEApp, MID_GNE_TOOLBAREDIT_LOADDEMAND);
    loadDemandInSUMOGUI->setCheck(TRUE);
    openInSUMOGUI = GUIDesigns::buildFXMenuCommand(editMenu,
        "Open in sumo-gui\tCtrl+T\tOpens the sumo-gui application with the current network.",
        GUIIconSubSys::getIcon(GUIIcon::SUMO_MINI), myGNEApp, MID_HOTKEY_CTRL_T_OPENSUMONETEDIT);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::ProcessingMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::ProcessingMenuCommands::ProcessingMenuCommands(GNEApplicationWindow* GNEApp) :
    computeNetwork(nullptr),
    computeNetworkVolatile(nullptr),
    cleanJunctions(nullptr),
    joinJunctions(nullptr),
    clearInvalidCrossings(nullptr),
    computeDemand(nullptr),
    cleanRoutes(nullptr),
    joinRoutes(nullptr),
    clearInvalidDemandElements(nullptr),
    optionMenus(nullptr),
    myGNEApp(GNEApp) {
}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::buildProcessingMenuCommands(FXMenuPane* fileMenu) {
    // build network processing menu commands
    computeNetwork = GUIDesigns::buildFXMenuCommand(fileMenu,
                                       "Compute Junctions\tF5\tCompute junction shape and logic.",
                                       GUIIconSubSys::getIcon(GUIIcon::COMPUTEJUNCTIONS), myGNEApp, MID_HOTKEY_F5_COMPUTE_NETWORK_DEMAND);
    computeNetworkVolatile = GUIDesigns::buildFXMenuCommand(fileMenu,
            "Compute Junctions with volatile options\tShift+F5\tCompute junction shape and logic using volatile junctions.",
            GUIIconSubSys::getIcon(GUIIcon::COMPUTEJUNCTIONS), myGNEApp, MID_HOTKEY_SHIFT_F5_COMPUTEJUNCTIONS_VOLATILE);
    cleanJunctions = GUIDesigns::buildFXMenuCommand(fileMenu,
                                       "Clean Junctions\tF6\tRemove solitary junctions.",
                                       GUIIconSubSys::getIcon(GUIIcon::CLEANJUNCTIONS), myGNEApp, MID_HOTKEY_F6_CLEAN_SOLITARYJUNCTIONS_UNUSEDROUTES);
    joinJunctions = GUIDesigns::buildFXMenuCommand(fileMenu,
                                      "Join Selected Junctions\tF7\tJoin selected junctions into a single junction.",
                                      GUIIconSubSys::getIcon(GUIIcon::JOINJUNCTIONS), myGNEApp, MID_HOTKEY_F7_JOIN_SELECTEDJUNCTIONS_ROUTES);
    clearInvalidCrossings = GUIDesigns::buildFXMenuCommand(fileMenu,
            "Clean invalid crossings\tF8\tClear invalid crossings.",
            GUIIconSubSys::getIcon(GUIIcon::JOINJUNCTIONS), myGNEApp, MID_HOTKEY_F8_CLEANINVALID_CROSSINGS_DEMANDELEMENTS);
    // build demand  processing menu commands
    computeDemand = GUIDesigns::buildFXMenuCommand(fileMenu,
                                      "Compute demand\tF5\tComputes demand elements.",
                                      GUIIconSubSys::getIcon(GUIIcon::COMPUTEDEMAND), myGNEApp, MID_HOTKEY_F5_COMPUTE_NETWORK_DEMAND);
    cleanRoutes = GUIDesigns::buildFXMenuCommand(fileMenu,
                                    "Clean routes\tF6\tRemoves routes without vehicles.",
                                    GUIIconSubSys::getIcon(GUIIcon::CLEANROUTES), myGNEApp, MID_HOTKEY_F6_CLEAN_SOLITARYJUNCTIONS_UNUSEDROUTES);
    joinRoutes = GUIDesigns::buildFXMenuCommand(fileMenu,
                                   "Join routes\tF7\tJoins routes with the same edges.",
                                   GUIIconSubSys::getIcon(GUIIcon::JOINROUTES), myGNEApp, MID_HOTKEY_F7_JOIN_SELECTEDJUNCTIONS_ROUTES);
    clearInvalidDemandElements = GUIDesigns::buildFXMenuCommand(fileMenu,
            "Clean invalid route elements\tF8\tClear elements with an invalid path (routes, Trips, Flows...).",
            GUIIconSubSys::getIcon(GUIIcon::JOINJUNCTIONS), myGNEApp, MID_HOTKEY_F8_CLEANINVALID_CROSSINGS_DEMANDELEMENTS);
    // add separator (because optionsmenu is commmon for Network and Demand modes
    new FXMenuSeparator(fileMenu);
    optionMenus = GUIDesigns::buildFXMenuCommand(fileMenu,
                                    "Options\tF10\tConfigure Processing Options.",
                                    GUIIconSubSys::getIcon(GUIIcon::OPTIONS), myGNEApp, MID_HOTKEY_F10_OPTIONSMENU);
}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::showNetworkProcessingMenuCommands() {
    // first enable menu commands
    computeNetwork->enable();
    computeNetworkVolatile->enable();
    cleanJunctions->enable();
    joinJunctions->enable();
    clearInvalidCrossings->enable();
    // now show it
    computeNetwork->show();
    computeNetworkVolatile->show();
    cleanJunctions->show();
    joinJunctions->show();
    clearInvalidCrossings->show();
}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::hideNetworkProcessingMenuCommands() {
    // first disable menu commands
    computeNetwork->disable();
    computeNetworkVolatile->disable();
    cleanJunctions->disable();
    joinJunctions->disable();
    clearInvalidCrossings->disable();
    // now hide it
    computeNetwork->hide();
    computeNetworkVolatile->hide();
    cleanJunctions->hide();
    joinJunctions->hide();
    clearInvalidCrossings->hide();
}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::showDemandProcessingMenuCommands() {
    // first enable menu commands
    computeDemand->enable();
    cleanRoutes->enable();
    joinRoutes->enable();
    clearInvalidDemandElements->enable();
    // now show it
    computeDemand->show();
    cleanRoutes->show();
    joinRoutes->show();
    clearInvalidDemandElements->show();
}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::hideDemandProcessingMenuCommands() {
    // first disable menu commands
    computeDemand->disable();
    cleanRoutes->disable();
    joinRoutes->disable();
    clearInvalidDemandElements->disable();
    // now hide it
    computeDemand->hide();
    cleanRoutes->hide();
    joinRoutes->hide();
    clearInvalidDemandElements->hide();
}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::showDataProcessingMenuCommands() {

}


void
GNEApplicationWindowHelper::ProcessingMenuCommands::hideDataProcessingMenuCommands() {

}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::LocateMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::LocateMenuCommands::LocateMenuCommands(GNEApplicationWindow* GNEApp) :
    myGNEApp(GNEApp) {
}


void
GNEApplicationWindowHelper::LocateMenuCommands::buildLocateMenuCommands(FXMenuPane* locateMenu) {
    // build locate menu commands
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Junctions\tShift+J\tOpen a dialog for locating a Junction.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEJUNCTION), myGNEApp, MID_LOCATEJUNCTION);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Edges\tShift+E\tOpen a dialog for locating an Edge.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEEDGE), myGNEApp, MID_LOCATEEDGE);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Vehicles\tShift+V\tOpen a dialog for locating a Vehicle.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEVEHICLE), myGNEApp, MID_LOCATEVEHICLE);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Persons\tShift+P\tOpen a dialog for locating a Person.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEPERSON), myGNEApp, MID_LOCATEPERSON);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Route\tShift+R\tOpen a dialog for locating a Route.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEROUTE), myGNEApp, MID_LOCATEROUTE);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Stops\tShift+S\tOpen a dialog for locating a Stop.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATESTOP), myGNEApp, MID_LOCATESTOP);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &TLS\tShift+T\tOpen a dialog for locating a Traffic Light.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATETLS), myGNEApp, MID_LOCATETLS);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate &Additional\tShift+A\tOpen a dialog for locating an Additional Structure.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEADD), myGNEApp, MID_LOCATEADD);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate P&oI\tShift+O\tOpen a dialog for locating a Point of Interest.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEPOI), myGNEApp, MID_LOCATEPOI);
    GUIDesigns::buildFXMenuCommand(locateMenu,
                      "Locate Po&lygon\tShift+L\tOpen a dialog for locating a Polygon.",
                      GUIIconSubSys::getIcon(GUIIcon::LOCATEPOLY), myGNEApp, MID_LOCATEPOLY);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::WindowsMenuCommands - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::WindowsMenuCommands::WindowsMenuCommands(GNEApplicationWindow* GNEApp) :
    myGNEApp(GNEApp) {
}


void
GNEApplicationWindowHelper::WindowsMenuCommands::buildWindowsMenuCommands(FXMenuPane* windowsMenu, FXStatusBar* statusbar, GUIMessageWindow* messageWindow) {
    // build windows menu commands
    GUIDesigns::buildFXMenuCheck(windowsMenu,
        "&Show Status Line\t\tToggle this Status Bar on/off.",
        nullptr, statusbar, FXWindow::ID_TOGGLESHOWN);
    GUIDesigns::buildFXMenuCheck(windowsMenu,
        "Show &Message Window\t\tToggle the Message Window on/off.",
        nullptr, messageWindow, FXWindow::ID_TOGGLESHOWN);
    GUIDesigns::buildFXMenuCommand(windowsMenu,
        "&Clear Message Window\t\tClear the Message Window.",
        nullptr, myGNEApp, MID_CLEARMESSAGEWINDOW);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper::NetworkCheckableButtons - methods
// ---------------------------------------------------------------------------

GNEApplicationWindowHelper::SupermodeCommands::SupermodeCommands(GNEApplicationWindow* GNEApp) :
    networkMode(nullptr),
    demandMode(nullptr),
    dataMode(nullptr),
    myGNEApp(GNEApp),
    myHorizontalSeparator(nullptr) {
}


void
GNEApplicationWindowHelper::SupermodeCommands::showSupermodeCommands() {
    networkMode->show();
    demandMode->show();
    dataMode->show();
    // also show separator
    myHorizontalSeparator->show();
}


void
GNEApplicationWindowHelper::SupermodeCommands::hideSupermodeCommands() {
    networkMode->hide();
    demandMode->hide();
    dataMode->hide();
    // also hide separator
    myHorizontalSeparator->hide();
}


void
GNEApplicationWindowHelper::SupermodeCommands::buildSupermodeCommands(FXMenuPane* editMenu) {
    // build supermode menu commands
    networkMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                    "&Network mode\tF2\tSelect network mode.",
                                    GUIIconSubSys::getIcon(GUIIcon::SUPERMODENETWORK), myGNEApp, MID_HOTKEY_F2_SUPERMODE_NETWORK);
    demandMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                   "&Demand mode\tF3\tSelect demand mode.",
                                   GUIIconSubSys::getIcon(GUIIcon::SUPERMODEDEMAND), myGNEApp, MID_HOTKEY_F3_SUPERMODE_DEMAND);
    dataMode = GUIDesigns::buildFXMenuCommand(editMenu,
                                 "&Data mode\tF4\tSelect data mode.",
                                 GUIIconSubSys::getIcon(GUIIcon::SUPERMODEDATA), myGNEApp, MID_HOTKEY_F4_SUPERMODE_DATA);
    // build separator
    myHorizontalSeparator = new FXMenuSeparator(editMenu);
}

// ---------------------------------------------------------------------------
// GNEApplicationWindowHelper - methods
// ---------------------------------------------------------------------------

bool
GNEApplicationWindowHelper::toogleEditOptionsNetwork(GNEViewNet* viewNet, const MFXCheckableButton* menuCheck, const int numericalKeyPressed, FXObject* obj, FXSelector sel) {
    // finally function correspond to visibleMenuCommands[numericalKeyPressed]
    if (menuCheck == viewNet->getNetworkViewOptions().menuCheckShowGrid) {
        // Toogle menuCheckShowGrid
        if (viewNet->getNetworkViewOptions().menuCheckShowGrid->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckShowGrid->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled toogle show grid throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckShowGrid->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled toogle show grid throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowGridNetwork
        viewNet->onCmdToogleShowGridNetwork(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckDrawSpreadVehicles) {
        // Toogle menuCheckDrawSpreadVehicles
        if (viewNet->getNetworkViewOptions().menuCheckDrawSpreadVehicles->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckDrawSpreadVehicles->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled toogle draw spread vehicles throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckDrawSpreadVehicles->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled toogle spread vehicles throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleDrawSpreadVehicles
        viewNet->onCmdToogleDrawSpreadVehicles(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckShowDemandElements) {
        // Toogle menuCheckShowDemandElements
        if (viewNet->getNetworkViewOptions().menuCheckShowDemandElements->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckShowDemandElements->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show demand elements throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckShowDemandElements->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show demand elements throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowDemandElements
        viewNet->onCmdToogleShowDemandElements(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckSelectEdges) {
        // Toogle menuCheckSelectEdges
        if (viewNet->getNetworkViewOptions().menuCheckSelectEdges->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckSelectEdges->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled select edges throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckSelectEdges->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled select edges throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleSelectEdges
        viewNet->onCmdToogleSelectEdges(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckShowConnections) {
        // Toogle menuCheckShowConnections
        if (viewNet->getNetworkViewOptions().menuCheckShowConnections->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckShowConnections->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show connections throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckShowConnections->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show connections throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowConnections
        viewNet->onCmdToogleShowConnections(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckHideConnections) {
        // Toogle menuCheckHideConnections
        if (viewNet->getNetworkViewOptions().menuCheckHideConnections->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckHideConnections->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled hide connections throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckHideConnections->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled hide connections throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleHideConnections
        viewNet->onCmdToogleHideConnections(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckExtendSelection) {
        // Toogle menuCheckExtendSelection
        if (viewNet->getNetworkViewOptions().menuCheckExtendSelection->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckExtendSelection->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled extend selection throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckExtendSelection->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled extend selection throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleExtendSelection
        viewNet->onCmdToogleExtendSelection(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckChangeAllPhases) {
        // Toogle menuCheckChangeAllPhases
        if (viewNet->getNetworkViewOptions().menuCheckChangeAllPhases->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckChangeAllPhases->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled change all phases throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckChangeAllPhases->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled change all phases throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleChangeAllPhases
        viewNet->onCmdToogleChangeAllPhases(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckWarnAboutMerge) {
        // Toogle menuCheckWarnAboutMerge
        if (viewNet->getNetworkViewOptions().menuCheckWarnAboutMerge->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckWarnAboutMerge->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled warn about merge throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckWarnAboutMerge->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled warn about merge throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleWarnAboutMerge
        viewNet->onCmdToogleWarnAboutMerge(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckShowJunctionBubble) {
        // Toogle menuCheckShowJunctionBubble
        if (viewNet->getNetworkViewOptions().menuCheckShowJunctionBubble->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckShowJunctionBubble->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show junction as bubble throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckShowJunctionBubble->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show junction as bubble throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowJunctionBubble
        viewNet->onCmdToogleShowJunctionBubbles(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckMoveElevation) {
        // Toogle menuCheckMoveElevation
        if (viewNet->getNetworkViewOptions().menuCheckMoveElevation->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckMoveElevation->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled move elevation throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckMoveElevation->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled move elevation throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleMoveElevation
        viewNet->onCmdToogleMoveElevation(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckChainEdges) {
        // Toogle menuCheckChainEdges
        if (viewNet->getNetworkViewOptions().menuCheckChainEdges->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckChainEdges->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled chain edges throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckChainEdges->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled chain edges throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleChainEdges
        viewNet->onCmdToogleChainEdges(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getNetworkViewOptions().menuCheckAutoOppositeEdge) {
        // Toogle menuCheckAutoOppositeEdge
        if (viewNet->getNetworkViewOptions().menuCheckAutoOppositeEdge->amChecked() == TRUE) {
            viewNet->getNetworkViewOptions().menuCheckAutoOppositeEdge->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled auto opposite edge throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getNetworkViewOptions().menuCheckAutoOppositeEdge->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled auto opposite edge throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleAutoOppositeEdge
        viewNet->onCmdToogleAutoOppositeEdge(obj, sel, nullptr);
    } else {
        return false;
    }
    return true;
}


bool
GNEApplicationWindowHelper::toogleEditOptionsDemand(GNEViewNet* viewNet, const MFXCheckableButton* menuCheck, const int numericalKeyPressed, FXObject* obj, FXSelector sel) {
    if (menuCheck == viewNet->getDemandViewOptions().menuCheckShowGrid) {
        // Toogle menuCheckShowGrid
        if (viewNet->getDemandViewOptions().menuCheckShowGrid->amChecked() == TRUE) {
            viewNet->getDemandViewOptions().menuCheckShowGrid->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled toogle show grid throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDemandViewOptions().menuCheckShowGrid->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled toogle show grid throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowGridDemand
        viewNet->onCmdToogleShowGridDemand(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDemandViewOptions().menuCheckDrawSpreadVehicles) {
        // Toogle menuCheckDrawSpreadVehicles
        if (viewNet->getDemandViewOptions().menuCheckDrawSpreadVehicles->amChecked() == TRUE) {
            viewNet->getDemandViewOptions().menuCheckDrawSpreadVehicles->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled toogle draw spread vehicles throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDemandViewOptions().menuCheckDrawSpreadVehicles->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled toogle spread vehicles throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleDrawSpreadVehicles
        viewNet->onCmdToogleDrawSpreadVehicles(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDemandViewOptions().menuCheckHideShapes) {
        // Toogle menuCheckHideShapes
        if (viewNet->getDemandViewOptions().menuCheckHideShapes->amChecked() == TRUE) {
            viewNet->getDemandViewOptions().menuCheckHideShapes->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled hide shapes throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDemandViewOptions().menuCheckHideShapes->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled hide shapes throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleHideNonInspecteDemandElements
        viewNet->onCmdToogleHideShapes(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDemandViewOptions().menuCheckHideNonInspectedDemandElements) {
        // Toogle menuCheckHideNonInspectedDemandElements
        if (viewNet->getDemandViewOptions().menuCheckHideNonInspectedDemandElements->amChecked() == TRUE) {
            viewNet->getDemandViewOptions().menuCheckHideNonInspectedDemandElements->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled hide non inspected demand elements throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDemandViewOptions().menuCheckHideNonInspectedDemandElements->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled hide non inspected demand elements throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleHideNonInspecteDemandElements
        viewNet->onCmdToogleHideNonInspecteDemandElements(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDemandViewOptions().menuCheckShowAllPersonPlans) {
        // Toogle menuCheckShowAllPersonPlans
        if (viewNet->getDemandViewOptions().menuCheckShowAllPersonPlans->amChecked() == TRUE) {
            viewNet->getDemandViewOptions().menuCheckShowAllPersonPlans->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show all person plans throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDemandViewOptions().menuCheckShowAllPersonPlans->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show all person plans throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleHideNonInspecteDemandElements
        viewNet->onCmdToogleHideNonInspecteDemandElements(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDemandViewOptions().menuCheckLockPerson) {
        // Toogle menuCheckShowAllPersonPlans
        if (viewNet->getDemandViewOptions().menuCheckLockPerson->amChecked() == TRUE) {
            viewNet->getDemandViewOptions().menuCheckLockPerson->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled lock person plan throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDemandViewOptions().menuCheckLockPerson->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled lock person plan throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleLockPerson
        viewNet->onCmdToogleLockPerson(obj, sel, nullptr);
    } else {
        return false;
    }
    return true;
}


bool
GNEApplicationWindowHelper::toogleEditOptionsData(GNEViewNet* viewNet, const MFXCheckableButton* menuCheck, const int numericalKeyPressed, FXObject* obj, FXSelector sel) {
    if (menuCheck == viewNet->getDataViewOptions().menuCheckShowAdditionals) {
        // Toogle menuCheckHideShapes
        if (viewNet->getDataViewOptions().menuCheckShowAdditionals->amChecked() == TRUE) {
            viewNet->getDataViewOptions().menuCheckShowAdditionals->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show additionals throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDataViewOptions().menuCheckShowAdditionals->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show shapes throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowAdditionals
        viewNet->onCmdToogleShowAdditionals(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDataViewOptions().menuCheckShowShapes) {
        // Toogle menuCheckHideShapes
        if (viewNet->getDataViewOptions().menuCheckShowShapes->amChecked() == TRUE) {
            viewNet->getDataViewOptions().menuCheckShowShapes->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show shapes throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDataViewOptions().menuCheckShowShapes->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show shapes throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowShapes
        viewNet->onCmdToogleShowShapes(obj, sel, nullptr);
    } else if (menuCheck == viewNet->getDataViewOptions().menuCheckShowDemandElements) {
        // Toogle menuCheckShowDemandElements
        if (viewNet->getDataViewOptions().menuCheckShowDemandElements->amChecked() == TRUE) {
            viewNet->getDataViewOptions().menuCheckShowDemandElements->setChecked(FALSE);
            // show extra information for tests
            WRITE_DEBUG("Disabled show demand elements throught alt + " + toString(numericalKeyPressed + 1));
        } else {
            viewNet->getDataViewOptions().menuCheckShowDemandElements->setChecked(TRUE);
            // show extra information for tests
            WRITE_DEBUG("Enabled show demand elements throught alt + " + toString(numericalKeyPressed + 1));
        }
        // Call manually onCmdToogleShowDemandElements
        viewNet->onCmdToogleShowDemandElements(obj, sel, nullptr);
    } else {
        return false;
    }
    return true;
}

/****************************************************************************/
