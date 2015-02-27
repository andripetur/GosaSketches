//
//  MeshFunctions.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__MeshFunctions__
#define __formRof__MeshFunctions__

#include "ofMain.h"
#include "ofxKinect.h"

class MeshFunctions
{
public: 
    MeshFunctions();
    
    ofMesh kinectToMesh(ofxKinect * kinect, int step);
    void colorMesh(ofMesh * mesh, ofFbo * fbo);
    
    void kinectToMesh(int step);
    
    void setKinectPointer();
    void setFboPointer();
    
    ofMesh mesh;
    ofxKinect *dasKinect;
    ofFbo * dasFbo;
    
};
#endif /* defined(__formRof__MeshFunctions__) */
