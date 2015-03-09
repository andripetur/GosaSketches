//
//  WorldSpinner.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 08/03/15.
//
//

#ifndef __formRof__WorldSpinner__
#define __formRof__WorldSpinner__

#include "ofMain.h"

class WorldSpinner
{
public:
    WorldSpinner();
    
    void update();
    void trigger();
    
    void spinWorld();
    
private:
    class spinVariables
    {
    public:
        float rotate = 0.f;
        float speed = (floor(ofRandom(3, 9)) * 0.1 );
        int direction = 1;
        bool bIsSpinning = false;
        float spinDestination = 0.f;
    };
    
    spinVariables x, y;
    
    void newDestination(spinVariables*var);
    void newDirection(spinVariables*var);
    void updateVar(spinVariables*var);
    
};
#endif /* defined(__formRof__WorldSpinner__) */
