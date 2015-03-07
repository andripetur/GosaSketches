//
//  MeshFunctions.cpp
//  formRof
//
//  Created by Andri Pétur Þrastarson on 27/02/15.
//
//

#include "MeshFunctions.h"

MeshFunctions::MeshFunctions()
{ }

void MeshFunctions::threadedFunction()
{
    
    while ( isThreadRunning() )
    {
        
        if ( newFrame )
        {
            lock();
                update();
                newFrame = false;
            unlock();
        }
        else
        {
            sleep( (1000.0/ofGetFrameRate())*0.5 );
        }
    }
    
}

//-------------------------------- Color Functions
void MeshFunctions::colorMesh()
{
    ofVec3f v;
    for ( int i = 0; i < mesh.getNumVertices(); ++i)
    {
        v = mesh.getVertex(i);
        mesh.addColor(colorSource.getColor( abs((int)v.x) % colorSource.getWidth(), abs((int)v.y) % colorSource.getHeight()) );
    }
}

void MeshFunctions::clearSourceToColor(ofColor bob)
{
    int numPix = colorSource.getWidth()*colorSource.getHeight();
    
    for ( int i = 0; i < numPix; ++i)
    {
        colorSource.setColor(i, bob);
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

void MeshFunctions::fillGrid(int step)
{
//    int step = 10;
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

void MeshFunctions::fillAbstractGrid(bool bWhichMethod)
{
    int step = 10;
    ofVec3f currentVec;
    float curDist;
    
    // Go through depth image, add vertexes
    for(int y = 0; y < dasKinect->getHeight(); y += step) {
        for(int x = 0; x < dasKinect->getWidth(); x += step) {
            if((curDist = dasKinect->getDistanceAt(x, y)) > 0
               )
            {
//                mesh.addColor(matisse.getColor(x+2, y*1.5));
                
                if ( bWhichMethod ) {
                    mesh.addVertex(dasKinect->getWorldCoordinateAt(sinTable[x]*x, sinTable[y]*y));
                } else {
                    mesh.addVertex(ofVec3f(
                                           sinTable[x]*wondTable[y] * sqrt(curDist),
                                           sinTable[y]*wondTable[x] * log(curDist),
                                           curDist ));
                }
            }
        }
    }
}

void MeshFunctions::fillAbstractForm(bool bSphereOrCone)
{
    int step = 5;
    float curDist;
    
    mesh2.clear();
    
    for(int y = 0; y < dasKinect->getHeight(); y += step) {
        for(int x = 0; x < dasKinect->getWidth(); x += step) {
            if((curDist = dasKinect->getDistanceAt(x, y)) > 0
               && curDist < 1700
               )
            {
//                mesh2.addColor(matisse.getColor(x+2, y*1.5));
                mesh2.addVertex(dasKinect->getWorldCoordinateAt(x, y));
                
            }
        }
    }
    
    // Select sphere or cone
    if ( bSphereOrCone )  {
        mesh = sphere.getMesh();
    }   else {
        mesh = cone.getMesh();
    }
    
    int numberOfVertices = mesh.getNumVertices();
    
    //Add the two meshesh together
    for ( int i = 0; i < numberOfVertices; ++i)
    {
//        mesh.addColor(mesh2.getColor(i));
        mesh.setVertex(i,  mesh.getVertex(i) + mesh2.getVertex(i) );
    }
}

void MeshFunctions::fillHumanDistortion()
{
    int step = 13;
    ofVec3f currentVec;
    float curDist;

    
    // Go through depth image, add vertexes
    for(int y = 0; y < dasKinect->getHeight(); y += step) {
        for(int x = 0; x < dasKinect->getWidth(); x += step) {
            if((curDist = dasKinect->getDistanceAt(x, y)) > 0
               && curDist < 1250
               )
            {
//                mesh.addColor(matisse.getColor(x+ofSignedNoise(theta)+2, y*1.5));
                currentVec = dasKinect->getWorldCoordinateAt(x, y);
                mesh.addVertex(currentVec.normalize() * dasKinect->getWorldCoordinateAt(x, y) );
                
                mesh.addVertex( dasKinect->getWorldCoordinateAt(x, y).rotateRad(TWO_PI/x, currentVec* dasKinect->getWorldCoordinateAt(x, y)));
                
            }
        }
    }
    
    // Remove vertexes that are very close to eachother
    ofVec3f vectA, vectB;
    for ( int i = 0; i < mesh.getNumVertices(); ++i)
    {
        vectA = mesh.getVertex(i);
        for (int y = i; y < mesh.getNumVertices(); ++y)
        {
            vectB = mesh.getVertex(y);
            
            if(vectA.distance(vectB) < 10)
            {
                mesh.removeVertex(y);
            }
        }
        
    }

}

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
    for (int a=0; a<numVerts-1; ++a)
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

void MeshFunctions::connectAbstractGrid(bool bWhichMethod)
{
    float connectionDistance;
    float minDistance;
    
    if ( bWhichMethod ) {
        minDistance = 30;
    } else {
        minDistance = 50;
    }
    
    connectionDistance = 80;
    
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
    
} //connectAbstract

void MeshFunctions::connectAbstractGridTriangles()
{
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.setupIndicesAuto();
}

void MeshFunctions::connectHumanDistortion()
{
    ofVec3f vecA, vecB;

    for (int i = 0; i < mesh.getNumVertices(); ++i ){
        vecA = mesh.getVertex(i);
        for ( int y = i; y < mesh.getNumVertices(); y+=2)
        {
            vecB = mesh.getVertex(y);
            
            vecA.squareDistance(vecB);
            
            if (vecA.length() < 650)
            {
                mesh.addIndex(y);
                
                if(vecA.distance(vecB) < 50) {
                    mesh.addIndex(i);
                }
            }
            
            
        }
    }
}


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
    glLineWidth(3);
//    ofEnableDepthTest();
    
//    flipKinectDrawing();
    ofScale(1, -1, 1);
    ofTranslate(0, 0, -1000);
    
    mesh.draw();
    
//	ofDisableDepthTest();
	ofPopMatrix();
}

void MeshFunctions::drawLines()
{
    mesh.setMode(OF_PRIMITIVE_LINES);
    glLineWidth(2);
    
    // the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, 1);
	ofTranslate(0, 0, -1000); // center the points a bit
    
    mesh.draw();
    
	ofPopMatrix();
}

void MeshFunctions::drawBoxes()
{
//    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofPushMatrix();
    
	flipKinectDrawing();
    
    int numVerts = mesh.getNumVertices();
    
    for ( int a=0; a < numVerts; ++a )
    {
        float biggerMaker = (((mesh.getVertex(a).z*-1)+1000)*0.01);
        ofSetColor(mesh.getColor(a));
        ofDrawBox(mesh.getVertex(a), 5, 5, (((mesh.getVertex(a).z*-1)+1000)*0.5) );
        
    }
    
	ofPopMatrix();
}

void MeshFunctions::drawTriangles()
{
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	ofPushMatrix();
    
    flipKinectDrawing();
    ofEnableDepthTest();
    
    mesh.draw();
    
	ofDisableDepthTest();
	ofPopMatrix();
}

void MeshFunctions::drawBlobs()
{
	ofPushMatrix();
    
    flipKinectDrawing();
    ofEnableDepthTest();
    
    mesh.draw();
    
	ofDisableDepthTest();
	ofPopMatrix();
}

void MeshFunctions::drawHumanDistortion(bool bPointsOrLines)
{
    ofPushMatrix();
    
    if (bPointsOrLines)
    {
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    else
    {
        mesh.setMode(OF_PRIMITIVE_LINES);
    }
    
	// the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, -1);
//	ofTranslate(0, 0, -1000); // center the points a bit
    
    float size  = mesh.getNumIndices()*0.001;
    glPointSize(size); // 3
    glLineWidth(size);
    mesh.draw();
    
	ofPopMatrix();
    
}

void MeshFunctions::drawGrowingHumanoid(bool bPointsOrLines)
{
    ofPushMatrix();
    
    if (bPointsOrLines)
    {
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    else
    {
        mesh.setMode(OF_PRIMITIVE_LINES);
    }
    
	// the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, 1);
	ofTranslate(0, 0, -1000); // center the points a bit
    
    float size  = ((mesh.getNumVertices()*-1.0)+3500)*0.01;
    glPointSize(size); // 3
    glLineWidth(size);
    mesh.draw();
    
	ofPopMatrix();
}

void MeshFunctions::flipKinectDrawing()
{
    // the projected points are 'upside down' and 'backwards'
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
}

// -----------------------------------------_look-up_tables--

int MeshFunctions::howWondrous(int input)
{
    int steps = 0;
    
    while (input != 1)
    {
        // if number is even :
        if ( input % 2 == 0 )
        {
            input *= 0.5;
            
            //if its odd :
        } else {
            input = (input * 3) + 1;
        }
        
        steps++;
        
        if(steps > 2000)
        {
            input = 1;
        }
    }
    
    return steps;
}

void MeshFunctions::fillLookUpTables()
{
    for ( int i = 0; i < LOOKUP_TABLE_SIZE; ++i)
    {
        sinTable[i] = sin(i);
        wondTable[i] = howWondrous(i);
    }
}

//-----------------------------------------GettersAndSetters

unsigned int MeshFunctions::getCurrentPreset()
{
    return preset;
}

void MeshFunctions::setPreset(unsigned int nPreset)
{
    preset = nPreset;
}

void MeshFunctions::setNewFrame()
{
    lock();
        newFrame = true;
    unlock();
}

//-----------------------------------------FormInitalizers
void MeshFunctions::initSphere()
{
    sphere.set(dasKinect->getWidth()*0.4, 40);
    sphere.setPosition(ofVec3f(ofGetWidth()*0.5,ofGetHeight()*0.5, -1000*sin(0) ));
}

void MeshFunctions::initCone()
{
    int res = 50;
    cone.setPosition(ofVec3f(ofGetWidth()*0.5,ofGetHeight()*0.5, -1000));
    cone.setResolution(res, res, res);
    cone.set(dasKinect->getWidth()*0.5, dasKinect->getHeight()*2);
}

