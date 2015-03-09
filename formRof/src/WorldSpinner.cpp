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
//        cout << "updating y" << endl;
        updateVar(&y);
    }
    
    if (x.bIsSpinning)
    {
//        cout << "updating x" << endl;
        updateVar(&x);
    }
}

void WorldSpinner::trigger()
{
    float rN = ofRandom(1.0);
    
    if ( rN <= 0.5)
    {
        y.bIsSpinning = false;
        
        newDirection(&x);
        newDestination(&x);
        x.bIsSpinning = true;
    }
    else
    {
        
        x.bIsSpinning = false;
        
        newDirection(&y);
        newDestination(&y);
        y.bIsSpinning = true;
    }
}

void WorldSpinner::newDestination(spinVariables * var)
{
 
    int rN = ofRandom(45.f, 90.f);
    var->spinDestination = 0.f;
    
    spinVariables pOrM;
    newDirection(&pOrM);
    
    var->spinDestination = fmod( fabs(var->rotate + ( rN * pOrM.direction )), 360.f);
    if( fabs(var->spinDestination - var->rotate) < 3.f ) newDestination(var);
    

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
    var->rotate += (var->speed * (float)var->direction);
    var->rotate =  fmod( var->rotate, 360 );
    
//    cout << "rotate: " << var->rotate << endl;
//    cout << "destination: " << var->spinDestination << endl;
//    cout << "speed: " << var->speed << endl;
    
    // Check if spin has reached it destination.
    if ( round(var->rotate) == round(var->spinDestination) )
    {
        var->bIsSpinning = false;
        var->rotate = round(var->spinDestination);
    }

}

void WorldSpinner::spinWorld()
{
    float yTrans = ofMap(y.rotate, 0.f, 360.f, ofGetHeight()*0.5f, 0.f);
    float xTrans = ofMap(x.rotate, 0.f, 360.f, ofGetWidth()*0.5f, 0.f);
    
    ofTranslate(0, yTrans);
        ofRotateY( y.rotate );
        
        ofTranslate(xTrans, 0);
            ofRotateX( x.rotate );
        ofTranslate(-xTrans, 0);
    
    ofTranslate(0, -yTrans);
    
}

