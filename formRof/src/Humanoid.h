//
//  Humanoid.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__Humanoid__
#define __formRof__Humanoid__

#include "ofMain.h"

class Humanoid {
    
public:
    Humanoid();
    ~Humanoid();
    
    void setup();
    void update();
    void draw();
    
private:
    ofMesh mesh;
};
#endif /* defined(__formRof__Humanoid__) */
