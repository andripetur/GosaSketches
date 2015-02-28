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
    
    void kinectToMesh(int step);
    void colorMesh();
    
    void setKinectPointer();
    void setFboPointer();
    
    ofMesh mesh;
    ofxKinect *dasKinect;
    ofFbo * dasFbo;
    
    ofPixels colorSource;
    
    //Fill functions
    void fillGrid();
    void fillLines();
    
    // Connect Functions
    void connectGrid();
    void connectLines(bool vs1or2); // dancinLines
    
    //DrawFunctions
    void drawPoints(); // plainPoints
    void drawGrid(); // KinectXxxxx
    void drawBoxes(); // kinectBoxes
    
};
#endif /* defined(__formRof__MeshFunctions__) */
