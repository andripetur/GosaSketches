//
//  minimal.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 19/02/15.
//
//

#include "ofApp.h"

#ifndef __formRof__minimal__
#define __formRof__minimal__

#include "ofxColorPalette.h"
#include "envelopeVariable.h"
#include "circle.h"
#include "Triangle.h"
#include "Square.h"

class Minimal
{

public:
    Minimal() {}
    Minimal(int width, int height);
    ~Minimal();
    
    // Functions
    void update();
    void draw();
    void drawTwoDee();
    void fillFbo();
    
    void drumTriggers(int which);
    
    // Sets and Gets
    ofFbo * getColorSourceFboPointer();
    
private:
    ofxColorPalette colorMatcher;
    
    ofFbo colorSource;
    
    unsigned int nrDrumHits;
    unsigned int nrKickHits; 
    unsigned int colorSwitchTrigger;
    
    Circle hringur;
    Triangle thrihorn;
    Square kassi;
    
    enum drmVariables
    {
        kickSpeed = 0,
        snareSpeed,
        nrOfDrmVar
    };
    envelopeVariable drmVar[nrOfDrmVar];
    
    
};
#endif /* defined(__formRof__minimal__) */