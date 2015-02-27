//
//  shape.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#ifndef __formRof__shape__
#define __formRof__shape__

#include "ofMain.h"

#define INIT_SIZE 20

class Shape
{
    
public:
    Shape();
    ~Shape();
    
    // Functions 
    virtual void drawTwoDim() = 0;
    virtual void drawThreeDim() = 0;
    
    void update();
    void checkEdges();
    void randomDirection();
    
    // Setters
    void setSize(float nSize);
    void setInitSize(float nInitSize);
    void setLocation(ofVec3f nLocation);
    void setDirection(ofVec3f nDirection);
    
    void setColor(ofColor nColor);
    void setRotateOn(bool nBool);
    
    // Getters
    float getSize();
    float getTheta();
    ofVec3f getLocation();
    ofColor getColor();
    
private:
    float size;
    float initSize;
    float shrinker = 0.5;
    
    bool rotateOn = true;
    float theta = 0;
    float spinSpeed = 0.5;
    
    ofColor color;
    
    ofVec3f location;
    ofVec3f direction;
    
};

#endif /* defined(__formRof__shape__) */
