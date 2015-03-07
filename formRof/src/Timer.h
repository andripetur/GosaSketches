//
//  timer.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 07/03/15.
//
//

#ifndef __formRof__timer__
#define __formRof__timer__

#include "ofMain.h"

class Timer
{
public:
    Timer();
    Timer(unsigned int beginTime, unsigned int length);
    
    bool checkTimer();
    
    void setLength(int length);
    unsigned int getTimerLength();
    unsigned int getTimeToNextDing();
    
private:
    unsigned int beginTime;
    unsigned int length;
    
    
};
#endif /* defined(__formRof__timer__) */
