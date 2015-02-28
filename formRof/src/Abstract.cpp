//
//  Abstract.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "Abstract.h"

Abstract::Abstract( ofxKinect *nKinect, ofFbo* nFbo )
{
    dasKinect = nKinect;
    dasFbo = nFbo; 
}

Abstract::~Abstract()
{
    
}

void Abstract::draw()
{}

void Abstract::update()
{}
