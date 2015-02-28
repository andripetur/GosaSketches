//
//  Humanoid.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__Humanoid__
#define __formRof__Humanoid__

#include "ofMain.h"
#include "ofxKinect.h"
#include "MeshFunctions.h"

enum PresetNames {PLAIN_POINTS = 0, GRID, LINES_ONE, LINES_TWO, BOXES, BOXES_TWO, NUMBER_OF_PRESETS};

class Humanoid : public MeshFunctions
{
    
public:
    Humanoid(ofxKinect *nKinect, ofFbo* nFbo);
    ~Humanoid();
    
    void update();
    void draw();
    
    void setPreset(int nPreset);
    int getCurrentPreset();
    
private:
    int preset;
};
#endif /* defined(__formRof__Humanoid__) */
