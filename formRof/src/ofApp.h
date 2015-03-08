#pragma once

#include "ofMain.h"
#include "oscRecieverThread.h"
#include "ofxKinect.h"
#include "ofxPostProcessing.h"
#include "minimal.h"
#include "Humanoid.h"
#include "Abstract.h"
#include "envelopeVariable.h"
#include "Timer.h"
#include "WorldSpinner.h"

enum drumTriggers {KICK = 0, SNARE, HH, PERC, COW};
enum sceneNames {MINIMAL = 0, HUMANOID, ABSTRACT};

class ofApp : public ofBaseApp
{
public:

// OpenFrameWorks Shiznit:
    ofApp();

    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);

// Osc Stuff
    void oscDrTriggerCallBack(int which);
    void oscEnergyCallback(float dasEnergy);
    void oscBpmCallback(float dasBpm);
    oscReceiverThread oscThread;

// Kinect Stuff :
    void setupKinect();

    ofxKinect kinect;
    float kinectAngle;
    float kinectAngleStart;

// Scenes
    Minimal minimal;
    Humanoid humanoid;
    Abstract abstract;

    int currentScene;
    
// Cam stuff
    ofEasyCam cam;
    WorldSpinner wSpin;

// After effects.
    ofxPostProcessing post;
    ofLight light,oppLight;

    KaleidoscopePass::Ptr kScope;
    BloomPass::Ptr bloom;
    NoiseWarpPass::Ptr nWarp;
    RGBShiftPass::Ptr rgbShift;
    PixelatePass::Ptr pixlate;
    VerticalTiltShifPass::Ptr verTiltShift;
    
    void setupPostProccessing();

    bool bAlpha = false;

//Envelopes
    enum pProcVariables
    {NOISE_AMP = 0, N_AMP_MOD, RGB_SHIFT_AMT, RGB_ANGLE, TILT_SHIFT, NR_P_PROC_VAR};
    envelopeVariable pProVar[NR_P_PROC_VAR];
    
// NoteLengths
    int currentBpm;
    void calcNoteLengths();
    
    enum noteLengths {_1n, _2n, _4n, _8n, _16n, _32n, NR_NVALUES};
    float nVal[NR_NVALUES];
// Timer
    Timer sceneTimer;
    void checkTimer(); 
        		
};
