//
//  circle.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__circle__
#define __formRof__circle__

#include "shape.h"

class Circle : public Shape {
    
public:
    
    Circle();
    
    void drawTwoDim();
    void drawThreeDim();
};

#endif /* defined(__formRof__circle__) */
