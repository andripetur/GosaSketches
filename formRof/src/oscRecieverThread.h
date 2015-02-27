//
//  oscRecieverThread.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 19/02/15.
//
//

#ifndef __formRof__oscReceiverThread__
#define __formRof__oscReceiverThread__

#include "ofxOsc.h"
#define PORT 9999

class ofApp;

class oscReceiverThread : public ofThread
{

public:
    oscReceiverThread(ofApp *setOwner);
    
    void threadedFunction();
    
private:
    ofApp * owner;
    
    ofxOscReceiver receiver;
    ofxOscMessage m;
    
    string messageAdress;
};

#endif /* defined(__formRof__oscReceiverThread__) */
