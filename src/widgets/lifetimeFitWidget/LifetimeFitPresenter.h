/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LifetimeFitPresenter.h
 * Author: petrstepanov
 *
 * Created on October 6, 2017, 6:31 PM
 */

#ifndef LifetimeFitPRESENTER_H
#define LifetimeFitPRESENTER_H

#include "../AbstractPresenter.h"
#include "LifetimeFitView.h"
#include "../../model/Model.h"

class LifetimeFitView;

class LifetimeFitPresenter : public AbstractPresenter<Model, LifetimeFitView> {
public:
    LifetimeFitPresenter(LifetimeFitView* view);

    // Override base class virtual methods
    Model* instantinateModel();

    void addEventListeners();
    // View functions

    void onFitSpectrumClicked();
    void onSaveImageClicked();
    void onSaveResultsClicked();
    void onClearResultsClicked();
    void onInitModel();
};

#endif /* LifetimeFitPRESENTER_H */
