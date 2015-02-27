//
//  Triangle.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "Triangle.h"

Triangle::Triangle()
{
    setLocation(ofVec3f(ofGetWidth()*0.75, ofGetHeight()*0.5, 0));
    setInitSize(INIT_SIZE);
    fillMesh();
    
}

void Triangle::drawTwoDim()
{
    ofSetColor(getColor());
    
}

void Triangle::drawThreeDim()
{
    ofSetColor(getColor());
    ofPushMatrix();
    
    {
        ofTranslate(getLocation().x, getLocation().y);
        ofRotateX(getTheta());
        
        ofScale( getSize(), getSize(), getSize());
        ofColor(color);
        mesh.draw();
        setColor(0);
        mesh.drawWireframe();
    
    }
    ofPopMatrix();
    
}

void Triangle::fillMesh()
{
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    mesh.addVertex(ofVec3f(0,0,1));
    mesh.addVertex(ofVec3f(0,2*sqrt(2),-1)/3);
    mesh.addVertex(ofVec3f(-sqrt(6),-sqrt(2),-1)/3);
    mesh.addVertex(ofVec3f(sqrt(6),-sqrt(2),-1)/3);
    mesh.addVertex(ofVec3f(0,0,1));
}
