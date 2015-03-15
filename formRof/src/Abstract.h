//
//  Abstract.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__Abstract__
#define __formRof__Abstract__

#include "ofMain.h"
#include "MeshFunctions.h"

class Abstract : public MeshFunctions
{
    
public:
    Abstract() {}
    Abstract( ofxKinect *nKinect, ofFbo* nFbo );
    ~Abstract();
    
    void update();
    void draw();
    
    void setPreset(int nPreset);
    string getCurrentPresetName();
    
private:
    enum AbstractPresets
    {
        AB_GRID_ONE = 0,
        AB_GRID_TWO,
        TRIANGLES_ONE,
        TRIANGLES_TWO,
        SPHERE_MORPH_DOTS,
        SPHERE_MORPH_BLOBS,
        SPHERE_MORPH_LINE_STRIPS,
        CONE_MORPH_DOTS,
        CONE_MORPH_BLOBS,
        CONE_MORPH_LINE_STRIPS,
        HUMAN_DISTORTION_DOTS,
        HUMAN_DISTORTION_LINES,
        HUMAN_DISTORTION_AU_DOTS,
        HUMAN_DISTORTION_AU_LINES,
        NR_OF_AB_PRESETS
    };
};

#endif /* defined(__formRof__Abstract__) */
