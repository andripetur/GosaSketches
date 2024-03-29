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

#define SIZE 100

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
    void flipRandomDirectionAxis();
    
    // Setters
    void setSize(float nSize);
    void setLocation(ofVec3f nLocation);
    void setDirection(ofVec3f nDirection);
    void setSpeed(float speed);
    
    void setColor(ofColor nColor);
    void setRotateOn(bool nBool);
    
    // Getters
    float getSize();
    float getTheta();
    ofVec3f getLocation();
    ofColor getColor();
    
    int sizeMulti = 6;
private:
    float size;
    
    bool rotateOn = true;
    float theta = 0;
    float spinSpeed = 0.5;
    
    float speed = 1;
    
    ofColor color;
    
    ofVec3f location;
    ofVec3f direction;
    
};

#endif /* defined(__formRof__shape__) */
