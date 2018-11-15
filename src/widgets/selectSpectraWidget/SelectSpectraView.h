/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SelectSpectraFrame.h
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#ifndef SELECTSPECTRAVIEW_H
#define SELECTSPECTRAVIEW_H

#include "../AbstractView.h"
#include "SelectSpectraPresenter.h"

class SelectSpectraPresenter;

class SelectSpectraView : public AbstractView<SelectSpectraPresenter> {
  protected:
    void initUI();

  private:
//    TGTextButton* btn;

  public:
    SelectSpectraView(const TGWindow *w = 0);
    virtual ~SelectSpectraView();

    // Override base class virtual functions
    SelectSpectraPresenter* instantinatePresenter();

    // Calls from Presenter
    
    // Calls to Presenter

    ClassDef(SelectSpectraView,0);
};

#endif /* SELECTSPECTRAVIEW_H */