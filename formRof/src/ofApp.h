#pragma once

#include "ofMain.h"
#include "oscRecieverThread.h"
#include "ofxKinect.h"
#include "minimal.h"

enum {KICK = 0, SNARE, HH, COW}; // drum triggers
enum {MINIMAL = 0, HUMANOID, ABSTRACT}; // current scene

class ofApp : public ofBaseApp{

	public:
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
    
    // Minimal scene
        Minimal minimal; 
    
    

		
};
