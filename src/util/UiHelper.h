/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UiHelper.h
 * Author: petrstepanov
 *
 * Created on October 11, 2017, 1:31 AM
 */

#ifndef UIHELPER_H
#define UIHELPER_H

#include <TGFileDialog.h>
#include <TGLabel.h>
#include <TGWindow.h>

class UiHelper {
public:
    static UiHelper* getInstance();
    static void setLabelColor(TGLabel* label, const char* color);

    int showOkDialog(const char* message);
    TList* getFilesFromDialog();
    void setMainFrame(TGWindow* window);

private:
    UiHelper();
    static UiHelper* instance;
    TGWindow* mainFrame = nullptr;
};

#endif /* UIHELPER_H */
