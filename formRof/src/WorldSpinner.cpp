//
//  WorldSpinner.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 08/03/15.
//
//

#include "WorldSpinner.h"

WorldSpinner::WorldSpinner()
{}

void WorldSpinner::update()
{
    if (y.bIsSpinning)
    {
        updateVar(&y);
    }
    
    if (x.bIsSpinning)
    {
        updateVar(&x);
    }
}

void WorldSpinner::trigger()
{
    float rN = ofRandom(1.0);
    if ( rN < 0.5)
    {
        x.bIsSpinning = true;
        y.bIsSpinning = false;
        newDirection(&x);
        newDestination(&x);
    }
    else
    {
        y.bIsSpinning = true;
        x.bIsSpinning = false;
        newDirection(&y);
        newDestination(&y);
    }
}

void WorldSpinner::newDestination(spinVariables * var)
{
 
    float rN = ofRandom(45, 90);
    
    spinVariables pOrM;
    newDirection(&pOrM);
    
    var->spinDestination = fabs(fmod(var->rotate + ( rN )*pOrM.direction, 360));
    

}

void WorldSpinner::newDirection(spinVariables *var)
{
    float rN = ofRandom(1.0);
    
    if (rN < 0.5)
    {
        var->direction = 1;
    }
    else
    {
        var->direction = -1;
    }
}

void WorldSpinner::updateVar(spinVariables *var)
{
    // Update them variables
    var->rotate += (var->speed * var->direction);
    var->rotate = fabs( fmod(var->rotate, 360) );
    
    // Check if spin has reached it destination.
    if ( fabs(var->rotate - var->spinDestination) < 3.0)
    {
        var->bIsSpinning = false;
    }

}

void WorldSpinner::spinWorld()
{
    int yTrans = ofMap(y.rotate, 0.f, 360.f, ofGetHeight()*0.5, 0.f);
    int xTrans = ofMap(x.rotate, 0.f, 360.f, ofGetWidth()*0.5, 0.f);
    
    ofTranslate(0, yTrans, 0);
    {
        ofRotateY( y.rotate );
        
        ofTranslate(xTrans, 0);
            ofRotateX( x.rotate );
        ofTranslate(-xTrans, 0);
    }
    ofTranslate(0, -yTrans, 0);
}

