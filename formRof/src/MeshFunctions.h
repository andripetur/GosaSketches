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

#define LOOKUP_TABLE_SIZE 2500

class MeshFunctions
{
public: 
    MeshFunctions();
    
    void kinectToMesh(int step);
    void colorMesh();
    
    ofMesh mesh,mesh2;
    ofxKinect *dasKinect;
    ofFbo * dasFbo;
    ofPixels colorSource;
    
    float sinTable[LOOKUP_TABLE_SIZE];
    int wondTable[LOOKUP_TABLE_SIZE];
    
    int howWondrous(int input);
    void fillLookUpTables(); 
    
    //Fill functions
    void fillGrid();
    void fillLines();
    void fillAbstractGrid(bool bWhichMethod);
    void fillAbstractForm();
    
    // Connect Functions
    void connectGrid();
    void connectLines(bool vs1or2); // dancinLines
    void connectAbstractGrid(bool bWhichMethod);
    void connectAbstractGridTriangles();
    
    //DrawFunctions
    void drawPoints(); // plainPoints
    void drawGrid(); // KinectXxxxx
    void drawBoxes(); // kinectBoxes
    void drawTriangles(); // kinectAbsttract verður betra með litum.
    void drawBlobs(); // spherMorphblob
    
    void flipKinectDrawing();
    
    int getCurrentPreset();
    void virtual setPreset(int nPreset);
    
    void initSphere();
    
private:
    int preset;
    ofSpherePrimitive sphere;
    
};
#endif /* defined(__formRof__MeshFunctions__) */
