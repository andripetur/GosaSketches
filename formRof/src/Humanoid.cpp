//
//  Humanoid.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "Humanoid.h"

Humanoid::Humanoid(ofxKinect *nKinect, ofFbo* nFbo)
{
    lock();
    dasKinect = nKinect;
    dasFbo = nFbo;
    
    colorSource.allocate(dasFbo->getWidth(), dasFbo->getHeight(), OF_IMAGE_COLOR);
    
    unlock();
    
    setNrOfPresets(HUMANOID_NR_OF_PRES);
    setPlaysZero();
    
    fillLookUpTables();
    
}

Humanoid::~Humanoid()
{
    
}

void Humanoid::update()
{    
    mesh.clear();
    clearSourceToColor(ofColor(255,255,255));
    
    switch ( getCurrentPreset() )
    {
        case PLAIN_POINTS:
            kinectToMesh(20);
            connectGrid();
            connectLines(true);
            break;
            
        case GROW_POINTS:
        case GROW_LINES:
            fillLines();
            break;
            
        case GRID:
            fillGrid(10);
            connectGrid();
            break;
            
        case LINES_ONE:
            fillLines();
            connectLines(TRUE);
            break;
            
        case LINES_TWO:
            fillLines();
            connectLines(FALSE);
            break;
            
        case BOXES:
            kinectToMesh(15);
            break;
            
        case BOXES_TWO:
            fillGrid(15);
            break;
    }
    
} // Update

void Humanoid::draw()
{
    
    lock();
    
    dasFbo->readToPixels(colorSource);
    colorMesh();
    
    switch ( getCurrentPreset() )
    {
        case PLAIN_POINTS:
            drawPoints();
            break;
        
        case GRID:
            drawGrid();
            break;
            
        case LINES_ONE:
        case LINES_TWO:
            drawLines();
            break;
            
        case BOXES:
        case BOXES_TWO:
            drawBoxes();
            break;
        
        case GROW_POINTS:
            drawGrowingHumanoid(true);
            break;
            
        case GROW_LINES:
            drawGrowingHumanoid(false);
            break;
            
    }
    unlock();
    
}

void Humanoid::setPreset(int nPreset)
{
    if (nPreset >= 0 && nPreset < HUMANOID_NR_OF_PRES)
    {
        MeshFunctions::setPreset( nPreset );
    }
}

