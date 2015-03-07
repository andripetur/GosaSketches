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
    lock();
    dasKinect = nKinect;
    dasFbo = nFbo;
    colorSource.allocate(dasFbo->getWidth(), dasFbo->getHeight(), OF_IMAGE_COLOR);
    
    unlock();
    fillLookUpTables();
    
    initSphere();
    initCone();
    
    setNrOfPresets(NR_OF_AB_PRESETS);
    setPlaysZero();

}

Abstract::~Abstract()
{}

void Abstract::update()
{
    mesh.clear();
    clearSourceToColor(ofColor(255,255,255));
    
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
            fillAbstractForm(true);
            break;
            
        case SPHERE_MORPH_LINE_STRIPS:
            mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
            fillAbstractForm(true);
            mesh.setupIndicesAuto();
            break;
        
        case CONE_MORPH_DOTS:
        case CONE_MORPH_BLOBS:
            fillAbstractForm(false);
            break;
            
        case CONE_MORPH_LINE_STRIPS:
            mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
            fillAbstractForm(false);
            mesh.setupIndicesAuto();
            break;
            
        case HUMAN_DISTORTION_DOTS:
        case HUMAN_DISTORTION_LINES:
            fillHumanDistortion();
            connectHumanDistortion();
            break;
        
        case HUMAN_DISTORTION_AU_DOTS:
        case HUMAN_DISTORTION_AU_LINES:
            fillHumanDistortion();
            mesh.setupIndicesAuto();
            break;
        
    
    }// switch

}

void Abstract::draw()
{
    lock();
    
    dasFbo->readToPixels(colorSource);
    colorMesh();
    
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
        case CONE_MORPH_DOTS:
            drawPoints();
            break;
        
        case SPHERE_MORPH_BLOBS:
        case CONE_MORPH_BLOBS:
        case SPHERE_MORPH_LINE_STRIPS:
        case CONE_MORPH_LINE_STRIPS:
            drawBlobs();
            break;
            
        case HUMAN_DISTORTION_DOTS:
        case HUMAN_DISTORTION_AU_DOTS:
            drawHumanDistortion(true);
            break;
            
        case HUMAN_DISTORTION_LINES:
        case HUMAN_DISTORTION_AU_LINES:
            drawHumanDistortion(false);
            break;
            
            
    }// switch
    unlock();
    
}

void Abstract::setPreset(int nPreset)
{
    if (nPreset >= 0 && nPreset < NR_OF_AB_PRESETS)
    {
        MeshFunctions::setPreset( nPreset );
    }
}
