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

class Humanoid : public MeshFunctions
{
    
public:
    
    Humanoid() {}
    Humanoid(ofxKinect *nKinect, ofFbo* nFbo);
    ~Humanoid();
    
    void update();
    void draw();
    
    void setPreset(int nPreset);
    string getCurrentPresetName();

private:
    enum HumanoidPresets
    {
        PLAIN_POINTS = 0,
        GROW_POINTS,
        GROW_LINES,
        GRID,
        LINES_ONE,
        LINES_TWO, BOXES,
        BOXES_TWO,
        HUMANOID_NR_OF_PRES
    };

};
#endif /* defined(__formRof__Humanoid__) */
