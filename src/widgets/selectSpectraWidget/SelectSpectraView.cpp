/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SelectSpectraFrame.cpp
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#include "SelectSpectraView.h"
#include "SelectSpectraPresenter.h"

using namespace RooFit;

ClassImp(SelectSpectraView)

SelectSpectraView::SelectSpectraView(const TGWindow* w) : AbstractView<SelectSpectraPresenter>(w){
    initUI();
    SelectSpectraPresenter* presenter = getPresenter();
    presenter->addEventListeners();
}

SelectSpectraPresenter* SelectSpectraView::instantinatePresenter(){
    return new SelectSpectraPresenter(this);
}

// Layout UI Elements
void SelectSpectraView::initUI(){
    SetLayoutManager(new TGHorizontalLayout(this));
}

// Calls from Presenter

// Calls to Presenter


SelectSpectraView::~SelectSpectraView() {
    Cleanup();
}
