//
//  NoteLengths.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 16/03/15.
//
//

#include "NoteLengths.h"

NoteLengths::NoteLengths()
{
    bpm = 120;
    calculateNoteLengths();
}

NoteLengths::NoteLengths(float bpm)
{
    this->bpm = bpm;
    calculateNoteLengths();
}

void NoteLengths::calculateNoteLengths()
{
    float wholeNote = (240000.f/(float)bpm);
    nLengths[_1n] = wholeNote;
    
    for ( int i = 1; i < NR_NLENGTHS; ++i )
    {
        nLengths[i] = nLengths[i-1] * 0.5;
    }
    
}

void NoteLengths::setBpm(float bpm)
{
    if (bpm != this->bpm)
    {
        this->bpm = bpm;
        calculateNoteLengths();
    }
}

float NoteLengths::getValue(int which)
{
    return nLengths[which];
}

float NoteLengths::getBpm()
{
    return bpm;
}
