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
#include "circle.h"
#include "Triangle.h"
#include "Square.h"

class Minimal {

public:
    Minimal(int width, int height);
    ~Minimal();
    
    // Functions
    void update();
    void draw();
    void fillFbo();
    
    void drumTriggers(int which);
    
    // Sets and Gets
    ofFbo * getColorSourceFboPointer();
    void setReductionSpeed(float nSpeed);
    
private:
    ofxColorPalette colorMatcher;
    
    ofFbo colorSource;
    
    unsigned int nrDrumHits;
    unsigned int colorSwitchTrigger;
    unsigned int growToSize = 200;
    
    float reductionSpeed;
    
    Circle hringur;
    Triangle thrihorn;
    Square kassi;
    
    
    
};
#endif /* defined(__formRof__minimal__) */