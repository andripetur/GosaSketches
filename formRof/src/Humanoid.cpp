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
    dasKinect = nKinect;
    dasFbo = nFbo;
    
    colorSource.allocate(dasFbo->getWidth(), dasFbo->getHeight(), OF_IMAGE_COLOR);
    fillLookUpTables();
    
}

Humanoid::~Humanoid()
{
    
}

void Humanoid::setPreset(int nPreset)
{
    if (nPreset >= 0 && nPreset < HUMANOID_NR_OF_PRES)
    {
        MeshFunctions::setPreset( nPreset );
    }
}

void Humanoid::update()
{
    mesh.clear();
    dasFbo->readToPixels(colorSource);
    
    switch ( getCurrentPreset() )
    {
        case PLAIN_POINTS:
            kinectToMesh(5);
            break;
            
        case GRID:
        case BOXES_TWO:
            fillGrid();
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
            kinectToMesh(10);
            break;
    }
    
    colorMesh();

} // Update

void Humanoid::draw()
{
    switch ( getCurrentPreset() )
    {
        case PLAIN_POINTS:
            drawPoints();
            break;
        
        case GRID:
        case LINES_ONE:
        case LINES_TWO:
            
            drawGrid();
            break;
            
        case BOXES:
        case BOXES_TWO:
            drawBoxes();
            break;
            
        
    }
    
}





