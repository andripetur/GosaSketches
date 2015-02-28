//
//  MeshFunctions.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "MeshFunctions.h"

MeshFunctions::MeshFunctions(){}
//-------------------------------- Color Functions
void MeshFunctions::colorMesh()
{
    for ( int i = 0; i < mesh.getNumIndices(); i++)
    {
        mesh.addColor(colorSource.getColor(i/colorSource.getWidth(), i/colorSource.getHeight()));
    }
}

//-------------------------------- Fill functions
void MeshFunctions::kinectToMesh(int step)
{
    for (int x = 0; x < dasKinect->getWidth(); x+= step) {
        for ( int y = 0; y < dasKinect->getHeight(); y+= step)
        {
            mesh.addVertex(dasKinect->getWorldCoordinateAt(x, y));
        }
    }
}

void MeshFunctions::fillGrid()
{
    int step = 10;
    ofVec3f currentVec;
    float curDist;
    
    // Go through depth image, add vertexes
    for(int y = 0; y < dasKinect->getHeight(); y += step) {
        for(int x = 0; x < dasKinect->getWidth(); x += step) {
            if((curDist = dasKinect->getDistanceAt(x, y)) > 0 &&
               curDist < 1250  )
            {
//                mesh.addColor(matisse.getColor(x+ofSignedNoise(theta)+2, y*1.5));
                mesh.addVertex(currentVec = dasKinect->getWorldCoordinateAt(x, y));
                mesh.addVertex(ofVec3f(currentVec.x, currentVec.y,(currentVec.z * -1) + 1500));
            }
        }
    }
}

void MeshFunctions::fillLines()
{
    int step = 10;
    ofVec3f currentVec;
    float curDist;

    // Go through depth image, add vertexes
    for(int y = 0; y < dasKinect->getHeight(); y += step) {
        for(int x = 0; x < dasKinect->getWidth(); x += step/2) {
            
            if((curDist = dasKinect->getDistanceAt(x, y)) > 0
               //                   && curDist < 1250
               )
            {
//                mesh.addColor(matisse.getColor(x+ofSignedNoise(theta)+2, y*1.5));
                mesh.addVertex(dasKinect->getWorldCoordinateAt(x, y));
            }
        }
    }
} //fillLines

//-------------------------------- Connect Functions
void MeshFunctions::connectGrid()
{
    float connectionDistance = 30;
    float minDistance = 20;
    int numVerts = mesh.getNumVertices();
    ofVec3f verta;
    ofVec3f vertb;
    
    float distance;
    
    //Go through vertexes and add lines inbetween them if they are close enough.
    for (int a=0; a<numVerts; ++a)
    {
        verta = mesh.getVertex(a);
        
        for (int b=a+1; b < numVerts; b+=3)
        {
            vertb = mesh.getVertex(b);
            distance = verta.distance(vertb);
            
            if (distance <= connectionDistance  &&
                distance > minDistance              )
            {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
            
        }
    }
    
} // connectGrid

void MeshFunctions::connectLines(bool vs1or2)
{
    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    ofVec3f verta;
    ofVec3f vertb;
    int step = 10;
    
    float distance;
    
    //Go through vertexes and add lines inbetween them if they are close enough.
    for (int a=0; a<numVerts-1; a++)
    {
        verta = mesh.getVertex(a); // Get first vertex
        
        if (vs1or2)
        {
            vertb = mesh.getVertex(a+1); // get second vertex
            
            // X value matches, add a line.
            if(verta.x == vertb.x )
            {
                mesh.addIndex(a);
                mesh.addIndex(a+1);
            }
            
        } else {
            
            vertb = mesh.getVertex(a + floor(dasKinect->getWidth()/step));
            
            if(verta.z == vertb.z )
            {
                mesh.addIndex(a);
                mesh.addIndex(a + floor(dasKinect->getWidth()/step));
            }
            
            vertb = mesh.getVertex(a + 1);
            distance = verta.distance(vertb);
            
            if(verta.y == vertb.y &&
               distance < connectionDistance)
            {
                mesh.addIndex(a);
                mesh.addIndex(a + 1);
            }
            
        }
    }
} // connectLines


//--------------------------------Draw functions
void MeshFunctions::drawPoints()
{
    glPointSize(5);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    mesh.drawVertices();
}

void MeshFunctions::drawGrid()
{
    mesh.setMode(OF_PRIMITIVE_LINES);
    
    // the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	ofEnableDepthTest();
    
    mesh.draw();
    
	ofDisableDepthTest();
	ofPopMatrix();
}

void MeshFunctions::drawBoxes()
{
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofPushMatrix();
    
	// the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	ofEnableDepthTest();
    
    int numVerts = mesh.getNumVertices();
    
    for ( int a=0; a < numVerts; ++a )
    {
        float biggerMaker = (((mesh.getVertex(a).z*-1)+1000)*0.01);
//        ofSetColor(mesh.getColor(a));
        ofDrawBox(mesh.getVertex(a), 5, 5, (((mesh.getVertex(a).z*-1)+1000)*0.5) );
        
    }
    
	ofDisableDepthTest();
	ofPopMatrix();
}



