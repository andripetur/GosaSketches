#include "ofApp.h"
//------------------Constructor_and_setup__Initalize_Dat_SHit------------
ofApp::ofApp() : oscThread(this) ,
                 minimal( ofGetWidth(), ofGetHeight() ) ,
                 humanoid(&kinect, minimal.getColorSourceFboPointer() ) ,
                 abstract(&kinect, minimal.getColorSourceFboPointer() )
{}

void ofApp::setup()
{
    ofSetFrameRate(33);
    setupKinect();
    
    // start from minimal scene.
    currentScene = MINIMAL;
    
    cam.enableMouseInput();
    
    // initalize postProcessing
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    
    // Setup light
	light.setPosition(1000, 1000, 2000);
    light.enable();
    
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>()->setEnabled(true);
    
//    kScope = post.createPass<KaleidoscopePass>();
//    kScope->setEnabled(true);
    
    rgbShift = post.createPass<RGBShiftPass>();
    rgbShift->setEnabled(true);
    
    bloom = post.createPass<BloomPass>();
    bloom->setEnabled(true);
    
    nWarp = post.createPass<NoiseWarpPass>();
    nWarp->setEnabled(true);
    
//    verTiltShift = post.createPass<VerticalTiltShifPass>();
//    verTiltShift->setEnabled(true);
    
    pProVar[NOISE_AMP] = envelopeVariable(0.f, 0.04, 522.f);
    pProVar[N_AMP_MOD] = envelopeVariable(1, 1.5, 100.f);
    pProVar[N_AMP_MOD].setSlope(envelopeVariable::COSINE);
    
    pProVar[RGB_SHIFT_AMT] = envelopeVariable(0.001f, 0.1, 1000.f);
    pProVar[RGB_SHIFT_AMT].setDirection( envelopeVariable::UP);
    pProVar[RGB_ANGLE] = envelopeVariable(0.001f, 0.1, 250);
    
//    pProVar[TILT_SHIFT] = envelopeVariable(0.0, 1.5, 500);
//    pProVar[TILT_SHIFT].setDirection( envelopeVariable::UP );
    
    //Start osc thread last to avoid calling unInitalized functions
    oscThread.startThread(true);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	kinect.setCameraTiltAngle(kinectAngleStart);
	kinect.close();
        
    //Receiver thread
    oscThread.waitForThread();
    
    //Close other running threads.
    if( abstract.isThreadRunning()) abstract.waitForThread();
    if( humanoid.isThreadRunning()) humanoid.waitForThread();
	
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Update the kinect
    kinect.update();
    
    minimal.update();
    minimal.update();
    
    // Update all envelopes
    for (int i = 0; i < NR_P_PROC_VAR; ++i)
    {
        pProVar[i].update();
    }
    
    nWarp->setAmplitude( pProVar[NOISE_AMP].getValue() * pProVar[N_AMP_MOD].getValue() );
    rgbShift->setAmount( pProVar[RGB_SHIFT_AMT].getValue() );
    rgbShift->setAngle( pProVar[RGB_ANGLE].getValue() );
//    verTiltShift->setH( pProVar[TILT_SHIFT].getValue() );
    
    switch ( currentScene )
    {
        case MINIMAL:
            // Close other scenes working threads if running.
            if( abstract.isThreadRunning()) abstract.waitForThread();
            if( humanoid.isThreadRunning()) humanoid.waitForThread();
            
            minimal.fillFbo();
            
            break;
            
        case HUMANOID:
            if(kinect.isFrameNew())
            {
                minimal.fillFbo();
                
                // If abs is running, close it.
                if(abstract.isThreadRunning()) abstract.waitForThread();
                
                // if hum isn't running start it.
                if (!humanoid.isThreadRunning()) humanoid.startThread(true);
                
                humanoid.setNewFrame();

            }
            break;
            
        case ABSTRACT:
            
            if(kinect.isFrameNew())
            {
                minimal.fillFbo();
                
                // if hum is running, close it.
                if(humanoid.isThreadRunning()) humanoid.waitForThread();
                
                // if abs ain't running, start it.
                if (!abstract.isThreadRunning()) abstract.startThread(true);
                
                abstract.setNewFrame();
            }
            break;
    }
    
    //Set fps as window title, if of is not fullscreen. 
    if ( ofGetWindowMode() != OF_FULLSCREEN )
    {
        ofSetWindowTitle(ofToString(ofGetFrameRate()));
    }
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // copy enable part of gl state
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    post.begin(cam);
    
    if(bAlpha) {
        ofBackground(0, 0, 0, 100);
    } else {
        ofBackground(0, 0, 0, 250);
    }

    switch ( currentScene )
    {
            
        case MINIMAL:
            minimal.draw();
//            minimal.drawTwoDee();
            break;
            
        case HUMANOID:
            humanoid.draw();
            break;
            
        case ABSTRACT:
            abstract.draw();
            break;
    }
    
    post.end();
    
//    minimal.draw();
    
    // set gl state back to original
    glPopAttrib();
    
    
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
    
    switch (which)
    {
        case KICK:
            pProVar[NOISE_AMP].trigger();
            break;
            
        case SNARE:
            pProVar[RGB_SHIFT_AMT].trigger();
            break;
            
        case HH:
            pProVar[N_AMP_MOD].trigger();
            break;
            
        case PERC:
            pProVar[RGB_ANGLE].trigger();
            break;
            
        case COW:
            
            break;
    }
    
}

void ofApp::oscEnergyCallback(float dasEnergy)
{
    
}

void ofApp::oscBpmCallback(float dasBpm )
{
    
}

//----------------User_Input--------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
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
            if ( currentScene == HUMANOID )
            {
                humanoid.setPreset( humanoid.getCurrentPreset() - 1 );
            }
            else if ( currentScene == ABSTRACT )
            {
                abstract.setPreset( abstract.getCurrentPreset() - 1 );
            }
            
            break;
            
        case OF_KEY_RIGHT:
            if ( currentScene == HUMANOID )
            {
                humanoid.setPreset( humanoid.getCurrentPreset() + 1 );
            }
            else if ( currentScene == ABSTRACT )
            {
                abstract.setPreset( abstract.getCurrentPreset() + 1 );
            }
            break;
            
        case 'a':
            bAlpha = !bAlpha;
            break;
            
        case ' ':
            
            break;
            
        } // switch

} // keyPressed

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
