//
//  minimal.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 19/02/15.
//
//

#include "minimal.h"

Minimal::Minimal(int width, int height) {
    
    //Allocate space for fbo
    colorSource.allocate(width, height);
    
    hringur.randomDirection();
    kassi.randomDirection();
    thrihorn.randomDirection();
    
    colorMatcher.setBaseColor(ofColor(255,100,200));
    colorMatcher.generateComplementaryTriad();
    
    nrDrumHits = 0;
    colorSwitchTrigger = 5;
    
}

Minimal::~Minimal() {
}

void Minimal::fillFbo()
{
    
    colorSource.begin();
    {
        hringur.drawTwoDim();
        kassi.drawTwoDim();
        thrihorn.drawTwoDim();
    }
    colorSource.end();
    
}

ofFbo * Minimal::getColorSourceFboPointer()
{
    return &colorSource;
}

void Minimal::drumTriggers(int which)
{
    
    switch (which)
    {
        case KICK:
            
            hringur.setSize(growToSize);
            break;
            
        case SNARE:
            
            kassi.setSize(growToSize*2);
            break;
            
        case HH:
            
            thrihorn.setSize(growToSize);
            break;
            
        case PERC:
            
            break;
            
        case COW:
            
            break;
    }
    
    nrDrumHits++;
    
    // Set new base color from the pallette every X hits.
    if ( (nrDrumHits % colorSwitchTrigger ) == 0 )
    {
        colorMatcher.setBaseColor(colorMatcher.getRandom());
        
        if (nrDrumHits % colorSwitchTrigger*10 == 0 )
        {
            colorMatcher.generateRandom();
        } else {
            colorMatcher.generateComplementaryTriad();
        }
    }
    
}// drumTriggers

void Minimal::setReductionSpeed(float nSpeed) {
    reductionSpeed = nSpeed;
}

void Minimal::update()
{
    hringur.update();
    kassi.update();
    thrihorn.update();
    
    hringur.setColor(colorMatcher[0]);
    kassi.setColor(colorMatcher[1]);
    thrihorn.setColor(colorMatcher[2]);
    
}

void Minimal::draw() {
    
    hringur.drawThreeDim();
    
    kassi.drawThreeDim();
    
    thrihorn.drawThreeDim();
    
}

