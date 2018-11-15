/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SelectSpectraPresenter.cpp
 * Author: petrstepanov
 *
 * Created on October 6, 2017, 6:31 PM
 */

#include "SelectSpectraPresenter.h"
#include "SelectSpectraView.h"
#include "../../model/Model.h"

SelectSpectraPresenter::SelectSpectraPresenter(SelectSpectraView* view) : AbstractPresenter<Model, SelectSpectraView>(view) {
    // Need to instantinate RooRealVarView model for source Contribution
//    Model* model = getModel();
}

Model* SelectSpectraPresenter::instantinateModel(){
    return Model::getInstance();
}

void SelectSpectraPresenter::onInitModel() {
    std::cout << "SelectSpectraPresenter::onInitModel" << std::endl;
}

void SelectSpectraPresenter::addEventListeners(){
    SelectSpectraView* view = getView();
    Model* model = getModel();
}
