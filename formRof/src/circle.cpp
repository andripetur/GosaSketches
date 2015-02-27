//
//  circle.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "circle.h"
Circle::Circle()
{
    setLocation( ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0 ) );
    
    setInitSize(INIT_SIZE);
}



void Circle::drawTwoDim()
{
    ofSetColor(getColor());
    ofEllipse( getLocation().x, getLocation().y, getSize(), getSize() );
}

void Circle::drawThreeDim()
{
    ofSetColor(getColor());
    ofDrawSphere( getLocation().x, getLocation().y, getLocation().z, getSize());
}
