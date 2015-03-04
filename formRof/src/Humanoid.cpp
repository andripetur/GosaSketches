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
    fillLookUpTables();
    
}

Humanoid::~Humanoid()
{
    
}

void Humanoid::update()
{
    mesh.clear();
    
//    dasFbo->readToPixels(colorSource);
    
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
    
//    colorMesh();
    
} // Update

void Humanoid::draw()
{
    lock();
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

