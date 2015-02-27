//
//  Triangle.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__Triangle__
#define __formRof__Triangle__

#include "shape.h"

class Triangle : public Shape {
    
public:
    
    Triangle();
    
    void drawTwoDim();
    void drawThreeDim();
    
private:
    ofMesh mesh;
    
    void fillMesh();
};

#endif /* defined(__formRof__Triangle__) */
