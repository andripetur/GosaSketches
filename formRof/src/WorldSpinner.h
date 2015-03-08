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
    struct spinVariables
    {
        float rotate = 0;
        float speed = ofRandom(0.3, 0.9);
        int direction;
        bool bIsSpinning = false;
        float spinDestination;
    };
    
    spinVariables x, y;
    
    void newDestination(spinVariables*var);
    void newDirection(spinVariables*var);
    void updateVar(spinVariables*var);
    
};
#endif /* defined(__formRof__WorldSpinner__) */
