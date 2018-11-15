/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SelectSpectraPresenter.h
 * Author: petrstepanov
 *
 * Created on October 6, 2017, 6:31 PM
 */

#ifndef SelectSpectraPRESENTER_H
#define SelectSpectraPRESENTER_H

#include "../AbstractPresenter.h"
#include "SelectSpectraView.h"
#include "../../model/Model.h"

class SelectSpectraView;

class SelectSpectraPresenter : public AbstractPresenter<Model, SelectSpectraView> {
public:
    SelectSpectraPresenter(SelectSpectraView* view);

    // Override base class virtual methods
    Model* instantinateModel();

    void addEventListeners();

    // View functions
};

#endif /* SelectSpectraPRESENTER_H */
