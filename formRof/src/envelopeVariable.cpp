//
//  envelopeVariable.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 02/03/15.
//
//

#include "envelopeVariable.h"

envelopeVariable::envelopeVariable()
{
    isTriggered = false;
    slope = LINEAR;
}

envelopeVariable::envelopeVariable(float _minValue, float _maxValue, float _decayLength)
{
    minValue = _minValue;
    maxValue = _maxValue;
    decayLength= _decayLength;
    
    slope = LINEAR;
    direction = DOWN;
    
    value=minValue;

}

void envelopeVariable::trigger()
{
    isTriggered = true;
    
    if ( direction == DOWN)
    {
        value = maxValue;
    }
    else
    {
        value = minValue;
    }
    
    calculateCrement();
}

void envelopeVariable::calculateCrement()
{
    int nFrames = floor( decayLength * 0.001 * ofGetFrameRate() );
    float distance = maxValue - minValue;
    
    if (slope == LINEAR)
    {
        decrement = (float)distance/nFrames;
    }
    else if ( slope == COSINE)
    {
        increment = M_PI * 0.5 / nFrames;
        
        if ( direction == DOWN)
        {
            theta = 0.0;
        }
        else
        {
            theta = M_PI * 0.5;
        }
    }
    
}

void envelopeVariable::update()
{
    if (isTriggered)
    {
        if (direction == DOWN)
        {
            if (slope == LINEAR)
            {
                value-=decrement;
            }
            else if ( slope == COSINE)
            {
                value = ofMap(cos(theta), 0.0, 1.0, minValue, maxValue);
                theta += increment;
            }
            
            if (value <= minValue)
            {
                isTriggered = false;
                value = minValue;
            }
        }
        else // direction UP
        {
            if (slope == LINEAR)
            {
                value+=decrement;
            }
            else if ( slope == COSINE)
            {
                value = ofMap(cos(theta), 0.0, 1.0, minValue, maxValue);
                theta -= increment;
            }
            
            if (value >= maxValue)
            {
                isTriggered = false;
                value = maxValue;
            }

        }
    }

} // update

// Gets and Sets
void envelopeVariable::setMinValue(float nMinValue) { minValue = nMinValue; }
void envelopeVariable::setMaxValue(float nMaxValue) { maxValue = nMaxValue; }
void envelopeVariable::setDecayLength(float nDecayLength) { decayLength = nDecayLength; }
void envelopeVariable::setSlope(int nSlope) { slope = nSlope; }
void envelopeVariable::setDirection(int nDirection) { nDirection = direction; }

float envelopeVariable::getValue() { return value; }
float envelopeVariable::getMinValue() { return minValue; }
float envelopeVariable::getMaxValue() { return maxValue; }
float envelopeVariable::getDecayLength() { return decayLength; }