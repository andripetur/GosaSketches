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
    Humanoid(ofxKinect *nKinect, ofFbo* nFbo);
    ~Humanoid();
    
    void update();
    void draw();
    
private:
    
};
#endif /* defined(__formRof__Humanoid__) */
