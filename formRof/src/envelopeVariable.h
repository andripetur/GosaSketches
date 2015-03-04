//
//  envelopeVariable.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 02/03/15.
//
//

#ifndef __formRof__envelopeVariable__
#define __formRof__envelopeVariable__
#include "ofMain.h"

class envelopeVariable 
{
public:
    envelopeVariable();
    envelopeVariable(float _minValue, float _maxValue, float _decayLength);
    
    enum slope {LINEAR = 0, COSINE , EXPONENTIAL};
    enum direction {DOWN = 0, UP};
    
    void trigger();
    void update();
    
    // Gets and Sets
    void setMinValue(float nMinValue);
    void setMaxValue(float nMaxValue);
    void setDecayLength(float nDecayLength);
    void setSlope(int nSlope);
    void setDirection(int nDirection);
    
    float getValue();
    float getMinValue();
    float getMaxValue();
    float getDecayLength();
    
private:
    bool isTriggered;
    
    float value;
    float minValue;
    float maxValue;
    float decayLength;
    
    int slope;
    int direction;
    
    float decrement;
    
    float increment, theta;
    
    void calculateCrement();
    
};
#endif /* defined(__formRof__envelopeVariable__) */
