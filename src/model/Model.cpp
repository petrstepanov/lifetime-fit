/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Model.cpp
 * Author: petrstepanov
 * 
 * Created on October 6, 2017, 2:35 AM
 */

#include "Model.h"

Model::Model(){
    // Assign default values to objects
    
};

Model* Model::instance = NULL;

Model* Model::getInstance(){
    if (!instance){
        instance = new Model();
    }
    return instance;
}

void Model::readFromFile(TFile* f) {

}

void Model::writeToFile(TFile* f) {

}
