/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MainView.cpp
 * Author: petrstepanov
 *
 * Created on October 15, 2017, 1:47 AM
 */

#include "MainView.h"
#include <TApplication.h>
#include "../model/Constants.h"
#include "../util/UiHelper.h"
#include <iostream>

MainView::MainView(const TGWindow* w) : TGMainFrame(w, Constants::windowWidth, Constants::windowHeight) {
  // Can cause segmentation violation https://root.cern.ch/root/html534/TGCompositeFrame.html#TGCompositeFrame:SetCleanup
  // SetCleanup(kDeepCleanup);
  // Set a name to the main frame
  SetWindowName(Constants::applicationName);
  // Close on Alt+F4
  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();
  // Pass TGMainFrame to UiHelper for centering the dialogs
  UiHelper* uiHelper = UiHelper::getInstance();
  uiHelper->setMainFrame(this);
}

MainView::~MainView(){
  Cleanup();
  delete this;
}

void MainView::mapAndResize(){
  // Map all subwindows of main frame
  MapSubwindows();
  // Initialize the layout algorithm
  Resize(GetDefaultSize());
  Resize(Constants::windowWidth, Constants::windowHeight);
  // Map main frame
  MapWindow();
}

void MainView::CloseWindow(){
  gApplication->Terminate(0);
}
