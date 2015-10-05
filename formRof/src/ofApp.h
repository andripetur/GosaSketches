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
#include "NoteLengths.h"

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

// Osc Stuff
    void oscDrTriggerCallBack(int which);
    void oscEnergyCallback(float dasEnergy);
    void oscBpmCallback(float dasBpm);
    void oscMidiCallback(int which, float value);
    
    float energy, roundedEnergy;
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
    bool sceneChangerEnabled;
    
// Cam stuff
    ofEasyCam cam;
    WorldSpinner wSpin;
    
    ofImage screen;
    Timer checkBlackTimer;     

// After effects.
    ofxPostProcessing post;
    ofLight light,oppLight;

    KaleidoscopePass::Ptr kScope;
    BloomPass::Ptr bloom;
    NoiseWarpPass::Ptr nWarp;
    RGBShiftPass::Ptr rgbShift;
    ContrastPass::Ptr contrast;
    
    void setupPostProccessing();

    bool bAlpha = false;
    float alpha;
    
    float brightness, ctrast;
    
    unsigned int hhCount;
    unsigned int percCount;

//Envelopes
    enum pProcVariables
    {
        NOISE_AMP = 0,  N_AMP_MOD,
        RGB_SHIFT_AMT,  RGB_ANGLE,
        TILT_SHIFT,     NR_P_PROC_VAR
    };
    envelopeVariable pProVar[NR_P_PROC_VAR];
    
// NoteLengths
    NoteLengths nLengths;
    
// Timer
    Timer sceneTimer;
    void checkTimer();
    
    bool bShowInfo = false;
};
