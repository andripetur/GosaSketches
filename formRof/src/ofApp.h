#pragma once

#include "ofMain.h"
#include "oscRecieverThread.h"
#include "ofxKinect.h"

enum {KICK = 0, SNARE, HH, COW};

class ofApp : public ofBaseApp{

	public:
        ofApp();

		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
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
    
    

		
};
