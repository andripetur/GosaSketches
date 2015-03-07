//
//  timer.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 07/03/15.
//
//

#include "Timer.h"

Timer::Timer()
{
    beginTime = 0;
    length = 10000;
}

Timer::Timer(unsigned int beginTime, unsigned int length)
{
    this->beginTime = beginTime;
    this->length = length;
}

bool Timer::checkTimer()
{
    if ( beginTime+length < ofGetElapsedTimeMillis() )
    {
        beginTime = ofGetElapsedTimeMillis();
        return true;
    }
    else
    {
        return false;
    }
}

void Timer::setLength(int length)
{
    this->length = length;
}

unsigned int Timer::getTimerLength()
{
    return length;
}

unsigned int Timer::getTimeToNextDing()
{
    int time = beginTime+length - ofGetElapsedTimeMillis();
    
    return time;
}
