#include "ofApp.h"
//------------------Constructor_and_setup__Initalize_Dat_SHit------------
ofApp::ofApp() : oscThread(this) ,
                 minimal( ofGetWidth(), ofGetHeight(), &nLengths ) ,
                 humanoid(&kinect, minimal.getColorSourceFboPointer() ) ,
                 abstract(&kinect, minimal.getColorSourceFboPointer() )
{}

void ofApp::setup()
{
    ofSetFrameRate(35);
    setupKinect();
    
    // start from minimal scene.
    currentScene = MINIMAL;
    energy = 0.01;
    roundedEnergy = 0.01;
    
    hhCount = 0;
    percCount = 0;
    sceneTimer.setLength( nLengths.getValue(NoteLengths::_1n)*4 );
    checkBlackTimer.setLength( 1000 );

    screen.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    
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
    
    kScope = post.createPass<KaleidoscopePass>();
    kScope->setEnabled(false);
    
    rgbShift = post.createPass<RGBShiftPass>();
    rgbShift->setEnabled(false);
    
    bloom = post.createPass<BloomPass>();
    bloom->setEnabled(true);
    
    nWarp = post.createPass<NoiseWarpPass>();
    nWarp->setEnabled(true);
    
    contrast = post.createPass<ContrastPass>();
    contrast->setEnabled(true);
    ctrast = brightness = 1.f;
    alpha = 255;
    
    // Initalize envelopes.
    pProVar[NOISE_AMP] = envelopeVariable(0.f, 0.04, 522.f);
    pProVar[N_AMP_MOD] = envelopeVariable(1, 1.5, 100.f);
    pProVar[N_AMP_MOD].setSlope(envelopeVariable::COSINE);
    
    pProVar[RGB_SHIFT_AMT] = envelopeVariable(0.001f, 0.1, 1000.f);
    pProVar[RGB_SHIFT_AMT].setDirection( envelopeVariable::UP);
    pProVar[RGB_ANGLE] = envelopeVariable(0.001f, 0.1, 250);

}

//--------------------------------------------------------------
void ofApp::exit()
{
	kinect.setCameraTiltAngle(kinectAngleStart);
	kinect.close();
        
    //Close oscReceiver thread
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
    
    // minimal always gets updated.
    minimal.update();
    
    // Update all envelopes
    for (int i = 0; i < NR_P_PROC_VAR; ++i) {
        pProVar[i].update();
    }
    
    // Update world spin 
    wSpin.update();
    
    // energy mapped to noisewarp amount. 
    nWarp->setAmplitude( ( pProVar[NOISE_AMP].getValue() * pProVar[N_AMP_MOD].getValue() ) * energy );
    
    // if rgbshift is enabled update that stuff.
    if(rgbShift->getEnabled()) {
        rgbShift->setAmount( pProVar[RGB_SHIFT_AMT].getValue() * roundedEnergy*2);
        rgbShift->setAngle( pProVar[RGB_ANGLE].getValue() );
    }
    
    contrast->setBrightness(brightness);
    contrast->setContrast(ctrast);
    
    // once a second check if screen is black
    if( checkBlackTimer.checkTimer() )
    {
        ofColor color = ofColor(0,0,0,255);
        screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight() );
        
        int crop = 50;
        for (int x = crop; x < ofGetWidth()-crop; ++x) {
            for ( int y = crop; y < ofGetHeight()-crop; ++y)
            {
                color += screen.getColor(x, y);
            }
        }
        
        // if screen is black trigger a spin.
        if (color == ofColor(0,0,0,255))
        {
            wSpin.trigger();
        }
    }
    
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
                // Draw background shape pixels.
                minimal.fillFbo();
                // Set length of Timer

                sceneTimer.setLength( nLengths.getValue(NoteLengths::_1n) * 8+(int(ofRandomf()*2)) );
                
                // If abs is running, close it.
                if(abstract.isThreadRunning()) abstract.waitForThread();
                
                // if hum isn't running start it.
                if(!humanoid.isThreadRunning()) humanoid.startThread(true);
                
                // Notify scene that there is new frame.
                humanoid.setNewFrame();
            }
            break;
            
        case ABSTRACT:
            
            if(kinect.isFrameNew())
            {
                // Draw background shape pixels.
                minimal.fillFbo();
                // Set length of Timer
                sceneTimer.setLength( nLengths.getValue(NoteLengths::_1n) * 4+(int(ofRandomf()*2)) );
                
                // if hum is running, close it.
                if(humanoid.isThreadRunning()) humanoid.waitForThread();
                
                // if abs ain't running, start it.
                if(!abstract.isThreadRunning()) abstract.startThread(true);
                
                // Notify scene that there is new frame.
                abstract.setNewFrame();
            }
            break;
    } // switch
    
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
        // Map energy amount to alpha color. More intensity lower alpha.
        ofBackground(0, 0, 0, ((energy * -1.f) + 1.f) * 200  );
    } else {
        ofBackground(0, 0, 0, alpha);
    }
    
    // Draw current scene
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
    
    // Draw minimalforms again ontop of pProcessing fbo for glitchy variations.
    if (currentScene == MINIMAL && fmod(roundedEnergy, 0.2f) < 0.05) {
        minimal.draw();
    }
    
    // set gl state back to original
    glPopAttrib();
    
    // Draw info to bottom left corner of screen
    if ( bShowInfo )
    {
        ofPoint pNameLoc = ofPoint(100, ofGetHeight() - 40);
        ofPoint sNameLoc = ofPoint(20, ofGetHeight() - 40);
        
        ofSetColor(255, 255 ,255);
        
        // scene and preset names
        switch (currentScene)
        {
            case MINIMAL:
                ofDrawBitmapString("Minimal", sNameLoc);
                break;
                
            case HUMANOID:
                ofDrawBitmapString("Humanoid", sNameLoc);
                abstract.lock();
                    ofDrawBitmapString( humanoid.getCurrentPresetName(), pNameLoc);
                abstract.unlock();
                break;
            
            case ABSTRACT:
                ofDrawBitmapString("Abstract", sNameLoc);
                humanoid.lock();
                    ofDrawBitmapString( abstract.getCurrentPresetName(), pNameLoc);
                humanoid.unlock();
                break;
        }
 
        // framerate
        ofDrawBitmapString( ofToString(ofGetFrameRate()), ofPoint(20, ofGetHeight() - 20));
        
        // bpm
        ofDrawBitmapString( ofToString(nLengths.getBpm()), ofPoint(100, ofGetHeight() - 20));
    }
}

//----------------Osc_Callback_funtions--------------------------
void ofApp::oscDrTriggerCallBack(int which)
{
    // Pass drum triggers on to minimal.
    minimal.drumTriggers(which);
    
    // Triggers
    switch (which)
    {
        case KICK:
            pProVar[NOISE_AMP].trigger();
            
            //Check preset change timer
            checkTimer();
            break;
            
        case SNARE:
            if (rgbShift->getEnabled()) {
                pProVar[RGB_SHIFT_AMT].trigger();
            }
            break;
            
        case HH:
        {
            pProVar[N_AMP_MOD].trigger();
            
            float rn = ofRandom(1);
            
            // If abstract is running throw some kaledeiscope in there
            if(currentScene == ABSTRACT)
            {
                if ( (hhCount & 1) != 0 )
                {
                    if (rn < 0.5)
                    {
                        kScope->setEnabled(!kScope->getEnabled());
                    }
                }
            }
            
            if ( (hhCount & 1) == 0 )
            {
                if (rn < 0.5)
                {
                    wSpin.trigger();
                }
            }
            
            ++hhCount;
        }
            break;
            
        case PERC:
        {
            // turn rgbShift on/off
            int h = hhCount % 3;
            int p = percCount % 7+currentScene;
            
            if ( h == p) {
                rgbShift->setEnabled(!rgbShift->getEnabled());
            }
            
            if (rgbShift->getEnabled()) {
                pProVar[RGB_ANGLE].trigger();
            }
            
            ++percCount;
        }
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
        if (sceneTimer.getTimeToNextDing() < nLengths.getValue(NoteLengths::_2n) )

        {
            bAlpha = true;
        }
    }
    
    energy = dasEnergy;
    roundedEnergy = roundf(energy * 1000) *0.0001; //round to two decimals
}

void ofApp::oscBpmCallback(float dasBpm )
{
    nLengths.setBpm(dasBpm);
    
    // if there's a new tempo edit envelope lengths.
    if (nLengths.getBpm() != dasBpm)
    {
        pProVar[NOISE_AMP] = envelopeVariable(0.f, 0.04, nLengths.getValue(NoteLengths::_4n) );
        pProVar[N_AMP_MOD] = envelopeVariable(1, 1.5, nLengths.getValue(NoteLengths::_16n) + nLengths.getValue(NoteLengths::_64n));
        
        pProVar[RGB_SHIFT_AMT] = envelopeVariable(0.001f, 0.1, nLengths.getValue(NoteLengths::_2n));
        pProVar[RGB_ANGLE] = envelopeVariable(0.001f, 0.1, nLengths.getValue(NoteLengths::_8n));
    }
}

void ofApp::oscMidiCallback(int which, float value)
{
    switch (which)
    {
        case 0:
        {   // Hipass mapped to brigthness
            float v = ofMap(value, 0.f, 127.f, 1.f, 25.f);
            brightness = v*v;
        }
            break;
            
        case 1:
        {   // lowpass mapped to contrast
            float v = ofMap(value, 0.f, 127.f, 5., 1.f);
            ctrast = v * v;
        }
            break;
            
        case 2:
            // reverb mapped to alpha
            if ( value == 0) {
                alpha = 255;
            } else {
                alpha = ofMap(value, 0., 127, 136.f, 77.f);
            }
            break;
            
        case 3: break;
        case 4: break;
        case 5: break;
            
    } // switch
    
}

void ofApp::checkTimer()
{
    if ( sceneTimer.checkTimer() )
    {
        if ( currentScene == HUMANOID) {
            humanoid.changePreset();
        }
        
        if ( currentScene == ABSTRACT ) {
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
			++kinectAngle;
			if(kinectAngle>30) kinectAngle=30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
			
		case OF_KEY_DOWN:
			--kinectAngle;
			if(kinectAngle<-30) kinectAngle=-30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
            
            // Select Scenes
        case '1': currentScene = MINIMAL;
            break;
        
        case '2': currentScene = HUMANOID;
            break;
            
        case '3': currentScene = ABSTRACT;
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
            
        case 'i':
        case 'I':
            bShowInfo = !bShowInfo; 
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
