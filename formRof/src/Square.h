//
//  Square.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__Square__
#define __formRof__Square__

#include "shape.h"

class Square : public Shape {
    
public:
    
    Square();
    
    void drawTwoDim();
    void drawThreeDim();
};

#endif /* defined(__formRof__Square__) */
