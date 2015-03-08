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
    currentBpm = 120;
    calcNoteLengths();
    
    sceneTimer.setLength( nVal[_1n]*4 );
    
    cam.enableMouseInput();
    
    // Setup light
	light.setPosition(1000, 1000, 2000);
    oppLight.setPosition(-1000, -1000, -2000);
    light.enable();
    oppLight.setDirectional();
    oppLight.enable();
    
    setupPostProccessing();
    
    //Start osc thread last to avoid calling unInitalized functions
    oscThread.startThread(true);
}

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

void ofApp::setupPostProccessing()
{
    // initalize postProcessing
    ofSetCoordHandedness(OF_RIGHT_HANDED);
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
    
    wSpin.update();
    
    nWarp->setAmplitude( pProVar[NOISE_AMP].getValue() * pProVar[N_AMP_MOD].getValue() );
    rgbShift->setAmount( pProVar[RGB_SHIFT_AMT].getValue() );
    rgbShift->setAngle( pProVar[RGB_ANGLE].getValue() );
//    verTiltShift->setH( pProVar[TILT_SHIFT].getValue() );
    
    // Update current scene
    switch ( currentScene )
    {
        case MINIMAL:
            // Close other scenes working threads if running.
            if( abstract.isThreadRunning()) abstract.waitForThread();
            if( humanoid.isThreadRunning()) humanoid.waitForThread();
            break;
            
        case HUMANOID:
            if(kinect.isFrameNew())
            {
                minimal.fillFbo();
                sceneTimer.setLength( nVal[_1n]*4 );
                
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
                sceneTimer.setLength( nVal[_1n] * 2 );
                
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
    
    if (currentScene == MINIMAL) {
        post.begin();
    } else {
        post.begin(cam);
        wSpin.spinWorld();
    }
    
    if(bAlpha) {
        ofBackground(0, 0, 0, 100);
    } else {
        ofBackground(0, 0, 0, 250);
    }
    
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
    
    post.end();
    
//    minimal.draw();
    
    // set gl state back to original
    glPopAttrib();
    
    // If app is fullscreen draw framerate in bottom left corner.
    if ( ofGetWindowMode() == OF_FULLSCREEN) {
        ofSetColor(255, 255 ,255);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(20, ofGetHeight() - 20));
    }
    
}

//----------------Osc_Callback_funtions--------------------------
void ofApp::oscDrTriggerCallBack(int which)
{
    minimal.drumTriggers(which);
    
    switch (which)
    {
        case KICK:
            pProVar[NOISE_AMP].trigger();
            checkTimer();
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
    } // switch
}

// ---------------- Scene chooser.
void ofApp::oscEnergyCallback(float dasEnergy)
{
    int lastScene = currentScene;
    
    if (dasEnergy < 0.3 )
    {
        currentScene = MINIMAL;
    }
    else if ( dasEnergy < 0.6)
    {
        currentScene = HUMANOID;
    }
    else
    {
        currentScene = ABSTRACT;  
    }
    
    // if time beetween scene switch and next preset change is shorter than
    // 1 second turn alpha down.
    if (lastScene != currentScene )
    {
        if (sceneTimer.getTimeToNextDing() < 1000)
        {
            bAlpha = true;
        }
    }
}

void ofApp::oscBpmCallback(float dasBpm )
{
    if (dasBpm != currentBpm)
    {
        dasBpm = currentBpm;
        calcNoteLengths();
    }
}

void ofApp::calcNoteLengths()
{
    float wholeNote = (240000.f/(float)currentBpm);
    nVal[_1n] = wholeNote;
    
    for ( int i = 1; i < NR_NVALUES; ++i )
    {
        nVal[i] = nVal[i-1] * 0.5;
    }

}

void ofApp::checkTimer()
{
    if ( sceneTimer.checkTimer() )
    {
        if ( currentScene == HUMANOID)
        {
            humanoid.changePreset();
        }
        
        if ( currentScene == ABSTRACT )
        {
            abstract.changePreset();
        }
        
        bAlpha = false;
    }
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
            
            // Turn alpha on/off.
        case 'a':
        case 'A':
            bAlpha = !bAlpha;
            break;
            
            // Trigger a spin
        case 's':
        case 'S':
            wSpin.trigger();
            break;
            
            // Trigger a preset change
        case ' ':
            if ( currentScene == HUMANOID )
            {
                humanoid.changePreset();
            }
            if ( currentScene == ABSTRACT )
            {
                abstract.changePreset();
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
