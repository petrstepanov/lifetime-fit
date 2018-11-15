/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LifetimeFitFrame.cpp
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#include "LifetimeFitView.h"
#include "LifetimeFitPresenter.h"
#include "../../model/Constants.h"
#include "../importSpectrumWidget/ImportSpectrumView.h"
#include "../importSpectrumWidget/ImportSourceSpectrumView.h"
#include "../../util/StringUtils.h"
#include <TGFrame.h>
#include <TGTextBuffer.h>
#include <TGText.h>
#include <TGDimension.h>
#include "../../util/UiHelper.h"
#include <map>
#include <sstream>
#include <TRootEmbeddedCanvas.h>
#include <TG3DLine.h>
#include "../../roofit/CompositeModelProvider.h"

using namespace RooFit;

ClassImp(LifetimeFitView)

//LifetimeFitView::LifetimeFitView(const TGWindow* w) : TGMainFrame(w, Constants::windowWidth, Constants::windowHeight){
LifetimeFitView::LifetimeFitView(const TGWindow* w) : AbstractView<LifetimeFitPresenter>(w){
    initUI();
    LifetimeFitPresenter* presenter = getPresenter();
    presenter->addEventListeners();
}

LifetimeFitPresenter* LifetimeFitView::instantinatePresenter(){
    return new LifetimeFitPresenter(this);
}

void LifetimeFitView::initUI(){
    SetLayoutManager(new TGHorizontalLayout(this));

    // Tabs widget
    tabsWidget = new TGTab(this, Constants::leftPanelWidth);

    // Import spectrum tab
    TGCompositeFrame *tabImport = tabsWidget->AddTab("Material Spectrum");
    tabImport->SetLayoutManager(new TGVerticalLayout(tabImport));
    tabImport->AddFrame(new ImportSpectrumView(tabImport), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, dx, dx, dy*2, dy*2));

    // Import Kapton spectrum tab
    TGCompositeFrame *tabImportKapton = tabsWidget->AddTab("Kapton Spectrum");
    tabImportKapton->SetLayoutManager(new TGVerticalLayout(tabImportKapton));
    tabImportKapton->AddFrame(new ImportSourceSpectrumView(tabImportKapton), new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, dx, dx, dy*2, dy*2));

    // Fit Data tab
    tabFit = tabsWidget->AddTab("Fit Data");
    tabFit->SetLayoutManager(new TGVerticalLayout(tabFit));

    // Fit Range Row
    TGHorizontalFrame *frameFitRange = new TGHorizontalFrame(tabFit);
    numFitMin = new TGNumberEntry(frameFitRange, -60, 4, -1, TGNumberFormat::kNESInteger,
            TGNumberFormat::kNEAAnyNumber,
            TGNumberFormat::kNELLimitMinMax,
            -9999, 9999);
    numFitMin->GetNumberEntry()->Connect("TextChanged(char*)", "LifetimeFitView", this, "onNumFitMinChanged()");

    numFitMax = new TGNumberEntry(frameFitRange, 60, 4, -1, TGNumberFormat::kNESInteger,
            TGNumberFormat::kNEAAnyNumber,
            TGNumberFormat::kNELLimitMinMax,
            -9999, 9999);
    numFitMax->GetNumberEntry()->Connect("TextChanged(char*)", "LifetimeFitView", this, "onNumFitMaxChanged()");
    frameFitRange->AddFrame(new TGLabel(frameFitRange, "Fit Range, keV"), new TGLayoutHints(kLHintsNormal, 0, 0, dy, 0));
    frameFitRange->AddFrame(numFitMax, new TGLayoutHints(kLHintsRight));
    frameFitRange->AddFrame(new TGLabel(frameFitRange, "-"), new TGLayoutHints(kLHintsRight, dx, dx, 3*dy/5, 0));
    frameFitRange->AddFrame(numFitMin, new TGLayoutHints(kLHintsRight));

    tabFit->AddFrame(frameFitRange, new TGLayoutHints(kLHintsExpandX, dx, dx, dy*2, dy));

    // Separator
    tabFit->AddFrame(new TGHorizontal3DLine(tabFit), new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    // Integration Parameters
    TGHorizontalFrame *frameSWidth = new TGHorizontalFrame(tabFit);
    lblRescale1 = new TGLabel(frameSWidth, "# x ");
    lblRescale1->SetTextJustify(kTextLeft);
    numSWidth = new TGNumberEntry(frameSWidth, 1.60, 4, -1, TGNumberFormat::kNESRealTwo,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMin,
            0.01, 9.99);
    frameSWidth->AddFrame(new TGLabel(frameSWidth, "S Region Width"), new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, 0, dy, 0));
    frameSWidth->AddFrame(numSWidth, new TGLayoutHints(kLHintsRight | kLHintsTop));
    frameSWidth->AddFrame(lblRescale1, new TGLayoutHints(kLHintsRight | kLHintsTop, 0, dx, 3*dy/5, 0));

    tabFit->AddFrame(frameSWidth, new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    TGHorizontalFrame *frameWWidth = new TGHorizontalFrame(tabFit);
    lblRescale2 = new TGLabel(frameWWidth, "# x ");
    numWWidth = new TGNumberEntry(frameWWidth, 3.00, 4, -1, TGNumberFormat::kNESRealTwo,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMin,
            0.01, 9.99);
    frameWWidth->AddFrame(new TGLabel(frameWWidth, "W Regions Width"), new TGLayoutHints(kLHintsNormal, 0, 0, dy, 0));
    frameWWidth->AddFrame(numWWidth, new TGLayoutHints(kLHintsRight));
    frameWWidth->AddFrame(lblRescale2, new TGLayoutHints(kLHintsRight, 0, dx, 3*dy/5, 0));

    tabFit->AddFrame(frameWWidth, new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    TGHorizontalFrame *frameWShift = new TGHorizontalFrame(tabFit);
    lblRescale3 = new TGLabel(frameWShift, "# x ");
    numWShift = new TGNumberEntry(frameWShift, 2.76, 4, -1, TGNumberFormat::kNESRealTwo,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMin,
            0.01, 9.99);
    frameWShift->AddFrame(new TGLabel(frameWShift, "W Regions Shift"), new TGLayoutHints(kLHintsNormal, 0, 0, dy, 0));
    frameWShift->AddFrame(numWShift, new TGLayoutHints(kLHintsRight));
    frameWShift->AddFrame(lblRescale3, new TGLayoutHints(kLHintsRight, 0, dx, 3*dy/5, 0));

    tabFit->AddFrame(frameWShift, new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    // Separator
    tabFit->AddFrame(new TGHorizontal3DLine(tabFit), new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    // Resolution Function Parameters
    TGHorizontalFrame* convolutionParamsFrame = new TGHorizontalFrame(tabFit);
    comboConvolutionType = new TGComboBox(convolutionParamsFrame, 0);
    std::map<Int_t, TString> convTypes = CompositeModelProvider::getConvolutionTypes();
    for (std::map<Int_t, TString>::iterator it=convTypes.begin(); it!=convTypes.end(); ++it){
        comboConvolutionType->AddEntry((it->second).Data(), it->first);
    }
    comboConvolutionType->Select(1);
    comboConvolutionType->Resize(75, 20);
    checkboxResFixed = new TGCheckButton(convolutionParamsFrame, "fixed");
    checkboxResFixed->SetOn();
    numResolutionFWHM = new TGNumberEntry(convolutionParamsFrame, 2.0, 4, -1, TGNumberFormat::kNESRealTwo,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMinMax,
            0.5, 4.0);
    convolutionParamsFrame->AddFrame(new TGLabel(convolutionParamsFrame, "Convolution"),
                                     new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, dx, 4*dy/5, 0));
    convolutionParamsFrame->AddFrame(comboConvolutionType, new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, 0, dy/5, 0));
    convolutionParamsFrame->AddFrame(checkboxResFixed, new TGLayoutHints(kLHintsRight | kLHintsTop, 0, 0, 3*dy/5, 0));
    convolutionParamsFrame->AddFrame(numResolutionFWHM, new TGLayoutHints(kLHintsRight | kLHintsTop, 0, dx, dy/5, 0));
    convolutionParamsFrame->AddFrame(new TGLabel(convolutionParamsFrame, "Resolution FWHM, keV"),
                                     new TGLayoutHints(kLHintsRight | kLHintsTop, 0, dx, 4*dy/5, 0));
    tabFit->AddFrame(convolutionParamsFrame, new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    // Separator
    tabFit->AddFrame(new TGHorizontal3DLine(tabFit), new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    // Add source contribution frame
    sourceContributionFrame = new TGVerticalFrame(tabFit);
    sourceContributionView = new RooRealVarView(sourceContributionFrame);
    sourceContributionFrame->AddFrame(sourceContributionView, new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));
    sourceContributionFrame->AddFrame(new TGHorizontal3DLine(sourceContributionFrame), new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));
    tabFit->AddFrame(sourceContributionFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX));

    // Model parameters
    TGHorizontalFrame* modelParamsFrame = new TGHorizontalFrame(tabFit);
    //	modelParamsFrame->AddFrame(new TGLabel(modelParamsFrame, "Model details:"), new TGLayoutHints(kLHintsNormal, 0, 30, 5, 0));
    checkboxHasParabola = new TGCheckButton(modelParamsFrame, "Parabola", -1);
    modelParamsFrame->AddFrame(checkboxHasParabola, new TGLayoutHints(kLHintsNormal, 0, 4*dx, 4*dy/5, 0));

    numGauss = new TGNumberEntry(modelParamsFrame, 3, 1, -1, TGNumberFormat::kNESInteger,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMinMax,
            0, 5);
    modelParamsFrame->AddFrame(numGauss, new TGLayoutHints(kLHintsNormal, 0, dx, 2*dy/5, 0));
    modelParamsFrame->AddFrame(new TGLabel(modelParamsFrame, "Gauss"), new TGLayoutHints(kLHintsNormal, 0, 3*dx, dy, 0));

    numExponent = new TGNumberEntry(modelParamsFrame, 0, 1, -1, TGNumberFormat::kNESInteger,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMinMax,
            0, 55);
    modelParamsFrame->AddFrame(numExponent, new TGLayoutHints(kLHintsNormal, 0, dx, 2*dy/5, 0));
    modelParamsFrame->AddFrame(new TGLabel(modelParamsFrame, "Exp"), new TGLayoutHints(kLHintsNormal, 0, 3*dx, dy, 0));

    numDampExponent = new TGNumberEntry(modelParamsFrame, 0, 1, -1, TGNumberFormat::kNESInteger,
            TGNumberFormat::kNEANonNegative,
            TGNumberFormat::kNELLimitMinMax,
            0, 5);
    modelParamsFrame->AddFrame(numDampExponent, new TGLayoutHints(kLHintsNormal, 0, dx, 2*dy/5, 0));
    modelParamsFrame->AddFrame(new TGLabel(modelParamsFrame, "Damping Exp"), new TGLayoutHints(kLHintsNormal, 0, 3*dx, dy, 0));

    tabFit->AddFrame(modelParamsFrame, new TGLayoutHints(kLHintsExpandX, dx, dx, dy, dy));

    // Fit Button
    TGHorizontalFrame* frameFitSpectrum = new TGHorizontalFrame(tabFit);
    btnFitSpectrum = new TGTextButton(frameFitSpectrum, "Fit and plot");
    btnFitSpectrum->Connect("Clicked()", "LifetimeFitView", this, "onFitSpectrumClicked()");
    frameFitSpectrum->AddFrame(btnFitSpectrum, new TGLayoutHints(kLHintsExpandX));
    tabFit->AddFrame(frameFitSpectrum, new TGLayoutHints(kLHintsExpandX, dx, dx, dy + 3, dy));

    // Fit Result TextBox
    txtFitResult = new TGTextEdit(tabFit);
    txtFitResult->SetBackgroundColor(Constants::colorAppWindow->GetPixel());
    tabFit->AddFrame(txtFitResult, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, dx, dx, dy, dy));

    TGHorizontalFrame* splitFrame = new TGHorizontalFrame(tabFit);

    btnClearResult = new TGTextButton(splitFrame, "Clear file");
    btnClearResult->Connect("Clicked()", "LifetimeFitView", this, "onClearResultsClicked()");
    splitFrame->AddFrame(btnClearResult, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, dx/2));
    btnSaveResult = new TGTextButton(splitFrame, "Save results");
    btnSaveResult->Connect("Clicked()", "LifetimeFitView", this, "onSaveResultsClicked()");
    splitFrame->AddFrame(btnSaveResult, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, dx/2));
    tabFit->AddFrame(splitFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, dx, dx, dy, 2*dy));

    // Attach Tabs Widget
    tabsWidget->SetTab(0);
    tabsWidget->SetWidth(Constants::leftPanelWidth); // Resize(tabsWidget->GetDefaultSize());
    AddFrame(tabsWidget, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY, dx, dx, 2*dy, 2*dy));

    // Right panel
    TGVerticalFrame* frameRightVertical = new TGVerticalFrame(this);
    TGHorizontalFrame* frameExportButtons = new TGHorizontalFrame(frameRightVertical);

    displayMin = new TGNumberEntry(frameExportButtons, 0, 5, -1, TGNumberFormat::kNESRealOne,
        TGNumberFormat::kNEAAnyNumber,
        TGNumberFormat::kNELLimitMinMax,
        -1000, 1000);
    displayMin->GetNumberEntry()->Connect("TextChanged(char*)", "LifetimeFitView", this, "onDisplayMinChange(char*)");
    frameExportButtons->AddFrame(displayMin, new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, dx, 0, 0));

    zoomSlider = new TGDoubleHSlider(frameExportButtons, 190, kDoubleScaleBoth, -1, kHorizontalFrame, GetDefaultFrameBackground(), kFALSE, kFALSE);
    zoomSlider->Connect("PositionChanged()", "LifetimeFitView",
                       this, "onSliderChange()");
    zoomSlider->SetRange(-60,60);
    zoomSlider->SetPosition(-60,60);
    frameExportButtons->AddFrame(zoomSlider, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, dx, dx, 0, 0));

    displayMax = new TGNumberEntry(frameExportButtons, 0, 5, -1, TGNumberFormat::kNESRealOne,
        TGNumberFormat::kNEAAnyNumber,
        TGNumberFormat::kNELLimitMinMax,
        -1000, 1000);
    displayMax->GetNumberEntry()->Connect("TextChanged(char*)", "LifetimeFitView", this, "onDisplayMaxChange(char*)");
    frameExportButtons->AddFrame(displayMax, new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, dx, 0, 0));

    // Save image button
    btnSaveImage = new TGTextButton(frameExportButtons, "Save Image");
    btnSaveImage->Connect("Clicked()", "LifetimeFitView", this, "onSaveImageClicked()");
    btnSaveImage->SetEnabled(false);
    frameExportButtons->AddFrame(btnSaveImage, new TGLayoutHints(kLHintsRight | kLHintsTop, 0, dx, 0, 0));

    setToolbarEnabled(kFALSE);

    // Attach Right Canvas (Plot)
    TRootEmbeddedCanvas *embedPlot = new TRootEmbeddedCanvas("embedPlot", frameRightVertical);
    frameRightVertical->AddFrame(embedPlot, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, dx, dx, dx));
    canvasPlot = embedPlot->GetCanvas();

    frameRightVertical->AddFrame(frameExportButtons, new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0));

    AddFrame(frameRightVertical, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 0, dx));

    // Plot Canvas Settings
    padData = new TPad("padData", "Pad for data", 0.0, 0.3, 1.0, 1.0, kWhite); // x_low, y_low, x_hi, y_hi
    padData->SetMargin(Constants::padMargin[0], Constants::padMargin[1], Constants::padMargin[2], Constants::padMargin[3]);
    padData->Draw();

    padChi2 = new TPad("padChi2", "Pad for chi^2", 0.0, 0.0, 1.0, 0.3, kWhite);
    padChi2->SetMargin(Constants::padMargin[0], Constants::padMargin[1], Constants::padMargin[2], Constants::padMargin[3]);
    padChi2->Draw();
}

// Calls from Presenter

LifetimeFitView::~LifetimeFitView() {
    Cleanup();
}
