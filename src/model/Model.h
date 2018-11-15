/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Model.h
 * Author: petrstepanov
 *
 * Created on October 6, 2017, 2:35 AM
 */

#ifndef MODEL_H
#define MODEL_H

#include <TFile.h>

class Model : public Object {
public:
    static Model* getInstance();

    static void writeToFile(TFile* f);
    static void readFromFile(TFile* f);

    // Getters and setters
    
    
private:
    Model(); // Private so that it can  not be called
    static Model* instance;

    TList* objects;
    
    // Spectra parameters
    
    // Fitting options
    
    // Graphs?
    
};

#endif /* MODEL_H */

