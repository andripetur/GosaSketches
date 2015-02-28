#include "ofApp.h"
//------------------Constructor_and_setup__Initalize_Dat_SHit------------
ofApp::ofApp() : oscThread(this) ,
                 minimal(ofGetWidth(),ofGetHeight() ) ,
                 humanoid(&kinect, minimal.getColorSourceFboPointer() ) ,
                 abstract(&kinect, minimal.getColorSourceFboPointer() ) {
}

void ofApp::setup()
{    
    ofSetFrameRate(60);
    setupKinect();
    
    oscThread.startThread(true);
    
    // start from minimal scene.
    currentScene = MINIMAL;
    
    cam.enableMouseInput();

}

//--------------------------------------------------------------
void ofApp::exit()
{
	kinect.setCameraTiltAngle(kinectAngleStart);
	kinect.close();
        
    //Receiver thread
    oscThread.waitForThread();
	
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Update the kinect
    kinect.update();
    minimal.update();

    switch ( currentScene )
    {
        case HUMANOID:
            if(kinect.isFrameNew())
            {
                minimal.fillFbo();
                humanoid.update();
            }
            break;
            
        case ABSTRACT:
            if(kinect.isFrameNew())
            {
                minimal.fillFbo();
                abstract.update();
            }
            break;
    }

	// If there is a new frame and we are connected
	if(kinect.isFrameNew())
    {
        //do Magic; 
    }
    
    //Set fps as window title, if of is not fullscreen. 
    if ( ofGetWindowMode() != OF_FULLSCREEN ) {
        ofSetWindowTitle(ofToString(ofGetFrameRate()));
    }
    
    minimal.update(); 
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0, 0, 0);
    
    cam.begin();
    
    switch ( currentScene )
    {
        case MINIMAL:
            minimal.draw();
            break;
            
        case HUMANOID:
            humanoid.draw();
            break;
            
        case ABSTRACT:
            abstract.draw();
            break;
    }
    
    cam.end();
    
    // If of is fullscreen draw framerate in bottom left corner.
    if ( ofGetWindowMode() == OF_FULLSCREEN) {
        ofSetColor(255, 255 ,255);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(20, ofGetHeight() - 20));
    }

}

//--------------------------------------------------------------
void ofApp::setupKinect()
{
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    // Initalise kinect - disable video image.
    kinect.init(false, false);
    
    // opens the kinect
    kinect.open();
    
    // setAngle on startup.
    kinectAngle = kinectAngleStart;
	kinect.setCameraTiltAngle(kinectAngle);
}

//----------------Osc_Callback_funtions--------------------------
void ofApp::oscDrTriggerCallBack(int which)
{
    minimal.drumTriggers(which);
}

void ofApp::oscEnergyCallback(float dasEnergy)
{
    
}

void ofApp::oscBpmCallback(float dasBpm)
{
    
}

//----------------User_Input--------------------------------------
void ofApp::keyPressed(int key)
{
    
    switch (key) {

            // open/close the kinect connection
		case 'o':
        case 'O':
			kinect.setCameraTiltAngle(kinectAngleStart); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
        case 'C':
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
            
            //FakeDrumHit
        case 'd':
        case 'D':
            minimal.drumTriggers(9);
            break;
            
            // Select Scenes
        case '1':
            currentScene = MINIMAL;
            break;
        
        case '2':
            currentScene = HUMANOID;
            break;
            
        case '3':
            currentScene = ABSTRACT;
            break;
            
            //Scroll Through Presets
        case OF_KEY_LEFT:
            if ( currentScene == HUMANOID ) {
                humanoid.setPreset( humanoid.getCurrentPreset() - 1 );
            } else if ( currentScene == ABSTRACT) {
                abstract.setPreset( abstract.getCurrentPreset() - 1 );
            }
            
            break;
            
        case OF_KEY_RIGHT:
            if ( currentScene == HUMANOID ) {
                humanoid.setPreset( humanoid.getCurrentPreset() + 1 );
            } else if ( currentScene == ABSTRACT) {
                abstract.setPreset( abstract.getCurrentPreset() + 1 );
            }
            break;
            
        } // switch

} // keyPressed

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
