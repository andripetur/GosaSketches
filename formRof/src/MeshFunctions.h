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

class MeshFunctions : public ofThread
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
    
    virtual void update() = 0;
    
    void threadedFunction();
    
    //Fill functions
    void fillGrid(int step);
    void fillLines();
    void fillAbstractGrid(bool bWhichMethod);
    void fillAbstractForm(bool bSphereOrCone);
    void fillHumanDistortion();
    
    // Connect Functions
    void connectGrid();
    void connectLines(bool vs1or2); // dancinLines
    void connectAbstractGrid(bool bWhichMethod);
    void connectAbstractGridTriangles();
    void connectHumanDistortion();
    
    //DrawFunctions
    void drawPoints(); // plainPoints
    void drawGrid(); // KinectXxxxx
    void drawLines();
    void drawBoxes(); // kinectBoxes
    void drawTriangles(); // kinectAbsttract verður betra með litum.
    void drawBlobs(); // spherMorphblob
    void drawHumanDistortion(bool bPointsOrLines);
    void drawGrowingHumanoid(bool bPointsOrLines);
    
    void flipKinectDrawing();
    
    unsigned int getCurrentPreset();
    void virtual setPreset(unsigned int nPreset);
    
    void setNewFrame();
    
    void initSphere();
    void initCone(); // resolution of form is a big influence on looks
    
private:
    bool newFrame = false;
    
    unsigned int preset;
    ofSpherePrimitive sphere;
    ofConePrimitive cone;
    
};
#endif /* defined(__formRof__MeshFunctions__) */
