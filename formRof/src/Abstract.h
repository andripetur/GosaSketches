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
    Abstract( ofxKinect *nKinect, ofFbo* nFbo );
    ~Abstract();
    
    void update();
    void draw();
    
    void setPreset(int nPreset);
    
private:
    enum AbstractPresets {AB_GRID_ONE = 0, AB_GRID_TWO, TRIANGLES_ONE, TRIANGLES_TWO, SPHERE_MORPH_DOTS, SPHERE_MORPH_BLOBS, SPHERE_MORPH_TRI_STRIPS,SPHERE_MORPH_LINE_STRIPS, NR_OF_AB_PRESETS};
};

#endif /* defined(__formRof__Abstract__) */
