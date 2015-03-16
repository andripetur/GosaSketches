//
//  minimal.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 19/02/15.
//
//

#include "minimal.h"

Minimal::Minimal(int width, int height, NoteLengths* nLengths) {
    
    //Allocate space for fbo
    colorSource.allocate(width, height);
    this->nLengths = nLengths;
    
    hringur.randomDirection();
    kassi.randomDirection();
    thrihorn.randomDirection();
    
    colorMatcher.setBaseColor(ofColor(255,100,200));
    colorMatcher.generateComplementaryTriad();
    
    nrDrumHits = 0;
    nrKickHits = 0;
    colorSwitchTrigger = 10;
    
    drmVar[kickSpeed] = envelopeVariable(1.f, 3.f, 750);
    drmVar[kickSpeed].setSlope( envelopeVariable::COSINE );
    
    drmVar[snareSpeed] = envelopeVariable(1, 2, 1000 );
    drmVar[snareSpeed].setSlope( envelopeVariable::COSINE );
    
}

Minimal::~Minimal() {
}

void Minimal::fillFbo()
{
    
    colorSource.begin();
    {
        ofBackground(255, 255, 255);
        
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
            drmVar[kickSpeed].trigger();
            
            if ( nrKickHits % 3 == 0)
            {
                hringur.randomDirection();
            }
            
            ++nrKickHits;
            break;
            
        case SNARE:  
            drmVar[snareSpeed].trigger();
            kassi.randomDirection();
            break;
            
        case HH:
            thrihorn.flipRandomDirectionAxis();
            break;
            
        case PERC:
            
            break;
            
        case COW:
            
            break;
    }
    
    ++nrDrumHits;
    
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

void Minimal::update()
{
    // Update envelopes
    for (int i = 0; i < nrOfDrmVar; ++i){
        drmVar[i].update();
    }
    
    hringur.setSpeed( drmVar[kickSpeed].getValue() );
    kassi.setSpeed( drmVar[snareSpeed].getValue() );
    
    // update shapes
    hringur.update();
    kassi.update();
    thrihorn.update();
    
    // set colors
    hringur.setColor(colorMatcher[0]);
    kassi.setColor(colorMatcher[1]);
    thrihorn.setColor(colorMatcher[2]);
    
}

void Minimal::draw() {
    
    hringur.drawThreeDim();
    
    kassi.drawThreeDim();
    
    thrihorn.drawThreeDim();
    
}

void Minimal::drawTwoDee()
{
    colorSource.draw(0, 0);
}

