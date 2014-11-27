//
//  Gaur.cpp
//  KinkaKolli
//
//  Created by Andri Pétur Þrastarson on 26/11/14.
//
//

#include "Gaur.h"

Gaur::Gaur(){}

Gaur::Gaur(Vec2f location, bool initState, int changeFreq)
{
    this->location = location;
    sameMirror = initState;
    this->changeFreq = changeFreq;
}

void Gaur::update()
{
    if(spin)
    {
        if(movementSpin != 35) {
            movementSpin++;
        }
    }else {
        if(movementSpin != 0) {
            movementSpin--;
        }
    }
    
    movement = (sin(theta)+0.4)*3;
    
    theta+= 0.1;
}

void Gaur::mouseClick(int howManyClicks)
{
    if(spin) {
        spin = false;
    } else {
        spin = true;
    }
    
    if(howManyClicks % changeFreq == 0)
    {
        if(sameMirror) {
            sameMirror = false;
        } else {
            sameMirror = true;
        }
    }
}

void Gaur::draw()
{
    // Hvíti hringur
    gl::color(255, 255, 255);
    gl::drawSolidCircle(location, radius);
    
    //Svarti Hringur
    gl::lineWidth(15);
    gl::color(0,0,0);
    gl::drawStrokedCircle(location, radius);
    
    //Augu
    gl::pushMatrices();
    
        if(sameMirror) {
            gl::translate( Vec2f(-movementSpin, movement));
        } else {
            gl::translate( Vec2f(movementSpin, movement));
        }
    
    int diss = 30;
    int lim = 25;
    
    
    if ( sameMirror && movementSpin > lim)
    {
        eyeWidthRight = 30 - movementSpin;
        
    } else {
        eyeWidthRight = 5;
    }
    

    if ( sameMirror == false && movementSpin > lim)
    {
        eyeWidthLeft = 30 - movementSpin;

    } else {
        eyeWidthLeft = 5;
    }
    
    
    if(sameMirror == false || movementSpin < diss)
    {
        // Hægra auga
        gl::color(0, 0, 0);
        gl::drawSolidEllipse( Vec2f( location.x-eyeSpace , location.y ), eyeWidthRight, 9);
    }
    
    if(sameMirror || movementSpin < diss)
    {
        // Vinstra auga
        gl::color(0, 0, 0);
        gl::drawSolidEllipse( Vec2f( location.x+eyeSpace , location.y ), eyeWidthLeft, 9);
    }
    
    gl::popMatrices();
    
    //Skítamix hringir til að fela að augað fari fyrir utan hausinn.
    /*
    gl::color( 0, 255, 255 );
    gl::drawStrokedCircle(location, radius+4);
    gl::drawStrokedCircle(location, radius+6);
    gl::drawStrokedCircle(location, radius+8);
    gl::drawStrokedCircle(location, radius+10);
    */
    
}

