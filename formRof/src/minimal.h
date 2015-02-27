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
    
    void update();
    void draw();
    void drumTriggers(int which);
    
    ofFbo * getColorSourceFboPointer();
    void setReductionSpeed(float nSpeed);
    
private:
    ofxColorPalette colorMatcher;
    
    ofFbo colorSource;
    
    ofSpherePrimitive sphere;
    ofBoxPrimitive box;
    
    void fillFbo();
    
    unsigned int nrDrumHits;
    unsigned int colorSwitchTrigger; 
    
    float reductionSpeed;
    
    Circle hringur;
    Triangle thrihorn;
    Square kassi;
    
    ofLight joi; 
    
    
};
#endif /* defined(__formRof__minimal__) */