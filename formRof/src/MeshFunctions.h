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
#define PLAY_ARRAY_SIZE 100

class MeshFunctions : public ofThread
{
public: 
    MeshFunctions();
    
    ofMesh mesh,mesh2;
    ofxKinect *dasKinect;
    ofFbo * dasFbo;
    ofPixels colorSource;
    
    virtual void update() = 0;
    void threadedFunction();
    
    // Color Functions
    void colorMesh();
    void clearSourceToColor(ofColor bob);
    
    //Fill functions
    void kinectToMesh(int step);
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
    void drawHumanDistortion(bool bPointsOrLines, bool bMorStill);
    void drawGrowingHumanoid(bool bPointsOrLines);
    
    void flipKinectDrawing();
    
    // Lookup table shiz
    float sinTable[LOOKUP_TABLE_SIZE];
    int wondTable[LOOKUP_TABLE_SIZE];
    int howWondrous(int input);
    void fillLookUpTables();
    
    // Gets and sets
    unsigned int getCurrentPreset();
    void virtual setPreset(unsigned int nPreset);
    void setNrOfPresets(unsigned int nrOfPresets);
    void setNewFrame();
    
    void initSphere();
    void initCone(); // resolution of form is a big influence on looks
    
    void changePreset();
    void setPlaysZero();
    
private:
    bool newFrame = false;
    
    unsigned int preset;
    unsigned int nrOfPresets;
    unsigned int nrOfPlays[PLAY_ARRAY_SIZE];
    
    unsigned int totalPlays;
    
    ofSpherePrimitive sphere;
    ofConePrimitive cone;
    
};
#endif /* defined(__formRof__MeshFunctions__) */
