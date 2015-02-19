#include "ofApp.h"



//--------------------------------------------------------------
ofApp::ofApp() : oscThread(this) , minimal(ofGetWidth(),ofGetHeight()) {
    
 
    
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    setupKinect();
    
    oscThread.startThread(true);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Update the kinect
    kinect.update();
	
	// If there is a new frame and we are connected
	if(kinect.isFrameNew())
    {
        //do Magic; 
    }
    
    //Set fps as window title.
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(ofRandom(255), ofRandom(255), ofRandom(255));

}

//--------------------------------------------------------------
void ofApp::setupKinect(){
    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    // Initalise kinect - disable video image.
    kinect.init(false, false);
    
    // opens the kinect
    kinect.open();
    
    kinectAngle = kinectAngleStart;
	kinect.setCameraTiltAngle(kinectAngle);
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    
	kinect.setCameraTiltAngle(kinectAngleStart);
	kinect.close();
    
    //Receiver thread
    oscThread.stopThread();
	
}

//----------------Osc_Callback_funtions--------------------------
void ofApp::oscDrTriggerCallBack(int which) {
    
    minimal.drumTriggers(which);
    
}

void ofApp::oscEnergyCallback(float dasEnergy) {
    
}

void ofApp::oscBpmCallback(float dasBpm) {
    
}

//----------------User_Input--------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {

            // close - open kinect connection
		case 'o':
			kinect.setCameraTiltAngle(kinectAngleStart); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
			
            //Adjust kinect angle
		case OF_KEY_UP:
			kinectAngle++;
			if(kinectAngle>30) kinectAngle=30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
			
		case OF_KEY_DOWN:
			kinectAngle--;
			if(kinectAngle<-30) kinectAngle=-30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
