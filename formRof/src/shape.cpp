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
    location += direction * speed;
    
    if (rotateOn)
    {
        theta += spinSpeed;
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
    
    if ( location.z > 0 || location.z < (ofGetHeight()*-1) )
    {
        direction.z *= -1;
    }
}

void Shape::randomDirection()
{
    direction = ofVec3f ( ofRandom(-2.,2), ofRandom(-2.,2), ofRandom(-2.,2));
}

void Shape::flipRandomDirectionAxis()
{
    float rn = ofRandom(1.f);
    
    if (rn > 0.3)
    {
        if (rn > 0.6)
        {
            direction.y *= -1;
        }
        else
        {
            direction.z *= -1;
        }
        
    }
    else // if smaller than 0.3
    {
        direction.x *= -1;
    }
    
}

// ------------------------ Setters
void Shape::setLocation(ofVec3f nLocation)
{ location = nLocation; }

void Shape::setDirection(ofVec3f nDirection)
{ direction = nDirection; }

void Shape::setSize(float nSize)
{ size = nSize; }

void Shape::setColor(ofColor nColor )
{ color = nColor; }

void Shape::setRotateOn(bool nBool)
{ rotateOn = nBool; }

void Shape::setSpeed(float speed)
{ this->speed = speed; }

// ------------------------Getters
ofVec3f Shape::getLocation()
{ return location; }

float Shape::getSize()
{ return size; }

float Shape::getTheta()
{ return theta; }

ofColor Shape::getColor()
{ return color; }
