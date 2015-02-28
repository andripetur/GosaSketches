//
//  Abstract.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "Abstract.h"

Abstract::Abstract( ofxKinect *nKinect, ofFbo* nFbo )
{
    dasKinect = nKinect;
    dasFbo = nFbo;
    
    colorSource.allocate(dasFbo->getWidth(), dasFbo->getHeight(), OF_IMAGE_COLOR);
    fillLookUpTables();
    
    initSphere();
}

Abstract::~Abstract()
{}

void Abstract::update()
{
    mesh.clear();
    
    switch ( getCurrentPreset() )
    {
        case AB_GRID_ONE:
            fillAbstractGrid(true);
            connectAbstractGrid(true);
            break;
            
        case AB_GRID_TWO:
            fillAbstractGrid(false);
            connectAbstractGrid(false);
            break;
            
        case TRIANGLES_ONE:
            fillAbstractGrid(true);
            connectAbstractGridTriangles();
            break;
            
        case TRIANGLES_TWO:
            fillAbstractGrid(false);
            connectAbstractGridTriangles();
            break;
            
        case SPHERE_MORPH_DOTS:
        case SPHERE_MORPH_BLOBS:
            fillAbstractForm();
            break;
        
        case SPHERE_MORPH_TRI_STRIPS:
            fillAbstractForm();
            connectAbstractGridTriangles();
            break;
            
        case SPHERE_MORPH_LINE_STRIPS:
            mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
            fillAbstractForm();
            mesh.setupIndicesAuto();
            break;
        
    
    }// switch

}

void Abstract::draw()
{
    switch ( getCurrentPreset() )
    {
        case AB_GRID_ONE:
        case AB_GRID_TWO:
            drawGrid();
            break;
            
        case TRIANGLES_ONE:
        case TRIANGLES_TWO:
            drawTriangles();
            break;
            
        case SPHERE_MORPH_DOTS:
            drawPoints();
            break;
        
        case SPHERE_MORPH_BLOBS:
        case SPHERE_MORPH_TRI_STRIPS:
        case SPHERE_MORPH_LINE_STRIPS:
            drawBlobs();
            break;
            
            
    }// switch
}

void Abstract::setPreset(int nPreset)
{
    if (nPreset >= 0 && nPreset < NR_OF_AB_PRESETS)
    {
        MeshFunctions::setPreset( nPreset );
    }
}