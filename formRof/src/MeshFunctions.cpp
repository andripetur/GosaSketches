//
//  MeshFunctions.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "MeshFunctions.h"

MeshFunctions::MeshFunctions(){}

ofMesh MeshFunctions::kinectToMesh(ofxKinect * kinect, int step)
{
    ofMesh returnMesh;
    
    for (int x = 0; x < kinect->getWidth(); x+= step) {
        for ( int y = 0; y < kinect->getHeight(); y+= step)
        {
            returnMesh.addVertex(kinect->getWorldCoordinateAt(x, y));
        }
    }
    
    return returnMesh;
}

void MeshFunctions::kinectToMesh(int step)
{
    for (int x = 0; x < dasKinect->getWidth(); x+= step) {
        for ( int y = 0; y < dasKinect->getHeight(); y+= step)
        {
            mesh.addVertex(dasKinect->getWorldCoordinateAt(x, y));
        }
    }
}

void MeshFunctions::colorMesh(ofMesh *mesh, ofFbo *fbo)
{
    for ( int i = 0; i < mesh->getNumIndices(); i++)
    {
        
    }
}

