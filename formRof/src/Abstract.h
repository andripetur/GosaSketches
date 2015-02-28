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
    
    void draw();
    void update();
    
private:
    
};

#endif /* defined(__formRof__Abstract__) */
