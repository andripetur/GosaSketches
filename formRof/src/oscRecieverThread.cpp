//
//  oscRecieverThread.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 19/02/15.
//
//

#include "oscRecieverThread.h"
#include "ofApp.h"

oscReceiverThread::oscReceiverThread(ofApp* setOwner)
{
    receiver.setup(PORT);
    owner = setOwner;
}

void oscReceiverThread::threadedFunction()
{
    // while thread is running
    while(isThreadRunning())
    {
        if (receiver.hasWaitingMessages() )
        {
            
            receiver.getNextMessage(&m);
            messageAdress = m.getAddress();
            
            if (messageAdress == "/kick")
            {
                owner->oscDrTriggerCallBack(KICK);
            }
            else if (messageAdress == "/snare")
            {
                owner->oscDrTriggerCallBack(SNARE);
            }
            else if (messageAdress == "/hh")
            {
                owner->oscDrTriggerCallBack(HH);
            }
            else if (messageAdress == "/perc")
            {
                owner->oscDrTriggerCallBack(PERC);
            }
            else if (messageAdress == "/cow")
            {
                owner->oscDrTriggerCallBack(COW);
            }
            else if (messageAdress == "/bpm")
            {
                owner->oscBpmCallback(m.getArgAsFloat(0));
            }
            else if (messageAdress == "/energy")
            {
                owner->oscEnergyCallback(m.getArgAsFloat(0));
            }
            else if (messageAdress == "/midi")
            {
                owner->oscMidiCallback(m.getArgAsInt32(0), m.getArgAsFloat(1));
            }

        }
        else
        {
            // If no wating message. Sleep one frame. 
            sleep(1000/ofGetFrameRate());
        }
        
    } // while

}
