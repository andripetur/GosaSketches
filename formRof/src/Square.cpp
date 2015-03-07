//
//  Square.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "Square.h"
Square::Square()
{
    setLocation(ofVec3f(ofGetWidth()*0.25, ofGetHeight()*0.5, 0));
    setInitSize(INIT_SIZE);
    
}

void Square::drawThreeDim()
{
    ofSetColor(getColor());
    ofPushMatrix();
        ofTranslate(getLocation().x, getLocation().y, getLocation().z);
        ofRotateX(getTheta());
        ofDrawBox(0, 0, 0, getSize());
    ofPopMatrix();
}

void Square::drawTwoDim()
{
    ofSetColor(getColor());
//    ofRect(getLocation().x, getLocation().y, getLocation().z, getSize(), getSize());
    ofRect(getLocation().x, getLocation().y, getSize() * sizeMulti, getSize() * sizeMulti);
}