//
//  Gaur.h
//  KinkaKolli
//
//  Created by Andri Pétur Þrastarson on 26/11/14.
//
//
#include "KinkaKolli_Prefix.pch"

#ifndef __KinkaKolli__Gaur__
#define __KinkaKolli__Gaur__

using namespace ci;
using namespace ci::app;
using namespace std;

class Gaur
{
public:
    Gaur();
    Gaur(Vec2f location, bool initState, int changeFreq);
    
    void update();
    void draw();
    void mouseClick(int howManyClicks);
    
private:
    int radius = 40;
    int eyeSpace = 10;
    
    int eyeWidthRight = 5;
    int eyeWidthLeft = 5;
    
    Vec2f location;
    
    bool sameMirror;
    bool spin = false;
    int changeFreq; 
    
    float movement = 0;
    float movementSpin = 35;
    float theta = 0.0;
    
    
    
};


#endif /* defined(__KinkaKolli__Gaur__) */
