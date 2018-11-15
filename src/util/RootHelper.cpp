/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RootHelper.cpp
 * Author: petrstepanov
 * 
 * Created on August 24, 2017, 8:16 PM
 */

#include "RootHelper.h"
#include <TUnixSystem.h>
#include <iostream>

void RootHelper::deleteObject(const char* name){
    TObject* obj = gROOT->FindObject(name);
    deleteObject(obj);
}

void RootHelper::deleteObject(TObject* obj){
    if (obj){
        obj->Delete();
//        delete obj;
    }
}

TNamed* RootHelper::getObjectFromList(TList* list, TString name){
    TIter next(list);
    TObject *obj;
    while (obj=(TNamed*)next()){
       TString objName(el->GetName());
       if(objName.CompareTo(name.c_str())==0){
           return objName;
       }
    }
    return NULL;
}

Int_t RootHelper::getNumCpu(){
    // Get number of CPUs
    SysInfo_t sysInfo;
    TSystem* tSystem = new TUnixSystem();
    tSystem->GetSysInfo(&sysInfo);
    std::cout << "NumCpu: " << sysInfo.fCpus << std::endl;
    return (sysInfo.fCpus >= 0) ? sysInfo.fCpus : 1;
}

TStopwatch* RootHelper::watch = new TStopwatch();

void RootHelper::startTimer(){
    watch->Start();    
}

void RootHelper::stopAndPrintTimer(){
    watch->Stop();
    watch->Print();
}