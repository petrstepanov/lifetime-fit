/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LifetimeFitFrame.h
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#ifndef LifetimeFitVIEW_H
#define LifetimeFitVIEW_H

#include <TGFrame.h>
#include <TString.h>
#include <TGLabel.h>
#include <TGTab.h>
#include <TGTextEdit.h>
#include <TGNumberEntry.h>
#include <TGComboBox.h>
#include <TGButton.h>
#include <TCanvas.h>
#include <TImage.h>
#include <TH1I.h>
#include <TH1F.h>
#include <RooCurve.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <TGDoubleSlider.h>
#include <TGTextEntry.h>
#include <TGTextBuffer.h>
#include "../AbstractView.h"
#include "LifetimeFitPresenter.h"

class LifetimeFitPresenter;

class LifetimeFitView : public AbstractView<LifetimeFitPresenter> {
  protected:
    void initUI();

  private:
    TGTextButton* btn;
    TGTab* tabsWidget;
    RooPlot* fitFrame;
    RooPlot* chiFrame;
    TPad* padData;
    TPad* padChi2;

  public:
    LifetimeFitView(const TGWindow *w = 0);
    virtual ~LifetimeFitView();

    // Override base class virtual functions
    LifetimeFitPresenter* instantinatePresenter();

    // Calls from Presenter

    // Calls to Presenter

    ClassDef(LifetimeFitView, 0);
};

#endif /* LifetimeFitVIEW_H */
