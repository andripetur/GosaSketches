//
//  shape.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "shape.h"

Shape::Shape() {}
Shape::~Shape() {}

// ------------------------ Functions

void Shape::update()
{
    location += direction;
    
    if (rotateOn)
    {
        theta += spinSpeed;
    }
    
    if ( size > initSize )
    {
        size -= shrinker;
    }
    
    checkEdges();
}

void Shape::checkEdges()
{
    if ( location.x > ofGetWidth() || location.x < 0)
    {
        direction.x *= -1;
    }
    
    if ( location.y > ofGetHeight() || location.y < 0)
    {
        direction.y *= -1;
    }
    
    if ( location.z > 0 || location.z < (ofGetHeight()*-1) ) {
        direction.z *= -1;
    }
}

void Shape::randomDirection()
{
    direction = ofVec3f ( ofRandom(-1.,1), ofRandom(-1.,1), ofRandom(-1.,1)); 
}

// ------------------------ Setters
void Shape::setLocation(ofVec3f nLocation)
{
    location = nLocation;
}

void Shape::setDirection(ofVec3f nDirection)
{
    direction = nDirection;
}

void Shape::setSize(float nSize) {
    
    size = nSize;
}

void Shape::setInitSize(float nInitSize)
{
    initSize = nInitSize;
    size = initSize; 
}

void Shape::setColor(ofColor nColor )
{
    color = nColor;
}

void Shape::setRotateOn(bool nBool)
{
    rotateOn = nBool;
}

// ------------------------Getters
ofVec3f Shape::getLocation()
{
    return location;
}

float Shape::getSize()
{
    return size;
}

float Shape::getTheta()
{
    return theta;
}

ofColor Shape::getColor()
{
    return color; 
}
