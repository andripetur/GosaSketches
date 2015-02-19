//
//  minimal.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 19/02/15.
//
//

#include "minimal.h"

Minimal::Minimal(int width, int height) {
    
    colorSource.allocate(width, height);
    
    sphere.set(20, 10);
}

Minimal::~Minimal() {
    colorSource.~ofFbo();
}

void Minimal::fillFbo() {
    
}

ofFbo * Minimal::getColorSourceFboPointer() {
    return &colorSource;
}

void Minimal::drumTriggers(int which) {
    
    switch (which) {
        case KICK:
            
            break;
            
        case SNARE:
            
            break;
            
        case HH:
            
            break;
            
        case COW:
            
            break;
    }
    
}

void Minimal::setReductionSpeed(float nSpeed) {
    reductionSpeed = nSpeed;
}

void Minimal::update() {
    
}

void Minimal::draw() {

}

