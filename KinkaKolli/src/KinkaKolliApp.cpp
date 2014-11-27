#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Gaur.h"

using namespace ci;
using namespace ci::app;
using namespace std;

float thetaY = 0;
float thetaX = 0;
float theta2 = 0;

bool nodOrShake = true;

Vec2f middle;
int radius = 40;
int eyeSpace = 10;

float movementY;
float movementX;

float movement2;
float movement2Spin = 35;

bool spin = true;
bool sameMirror = true;
bool sameMirror2 = false;

Gaur gaur[10];

int countClicks;

class KinkaKolliApp : public AppNative {
  public:
	void setup();
	void prepareSettings( Settings *settings ) override;
	void mouseDown( MouseEvent event );
	void update();
	void draw();
};

void KinkaKolliApp::prepareSettings( Settings *settings )
{
	settings->enableHighDensityDisplay();
	settings->enableMultiTouch( false );
	
}

void KinkaKolliApp::setup()
{
    middle = getWindowSize()/2;
    
    for (int i = 0; i < 10; i++) {
        gaur[i] = Gaur( Vec2<int>(i*50, i*50), true, (i+1)*2);
    }
}

void KinkaKolliApp::mouseDown( MouseEvent event )
{
    for (int i = 0; i < 10; i++) {
        gaur[i].mouseClick(countClicks);
    }
    
    if(spin) {
        spin = false;
    } else {
        spin = true;
    }
    
    countClicks++;
    
    if(countClicks % 2 == 0)
    {
        if(sameMirror) {
            sameMirror = false;
        } else {
            sameMirror = true;
        }
    }
    
    if(countClicks % 4 == 0)
    {
        if(sameMirror2) {
            sameMirror2 = false;
        } else {
            sameMirror2 = true;
        }
    }
    
}

void KinkaKolliApp::update()
{
    for (int i = 0; i < 10; i++) {
        gaur[i].update();
    }
    
    if(nodOrShake){
        thetaY += 0.1;
    } else {
        thetaX += 0.1;
    }
    
    theta2 += 0.1;
    
    if(fmod(getElapsedFrames(),80) == 0){
        if(nodOrShake){
            nodOrShake = false;
        } else {
            nodOrShake = true;
        }
    }//if
    
    movementY = (sin(thetaY)+0.4)*3;
    movementX = (sin(thetaX)+0.4)*3;
    movement2 = (sin(theta2)+0.4)*3;
    
    if(spin)
    {
        if(movement2Spin != 35) {
            movement2Spin++;
        }
    }else {
        if(movement2Spin != 0) {
            movement2Spin--;
        }
    }
    
}

void KinkaKolliApp::draw()
{
    
//	// clear out the window with black
	gl::clear( Color( 0, 255, 255 ) );
//
//    gl::pushMatrices();
//        gl::translate( Vec2f( -middle.x/2, 0) );
//        
//        // Hvíti hringur
//        gl::color(255, 255, 255);
//        gl::drawSolidCircle(middle, radius);
//        
//        //Svarti Hringur
//        gl::color(0, 0, 0);
//        gl::lineWidth(15);
//        
//        gl::drawStrokedCircle(middle, radius);
//        
//        //Augu
//        
//        gl::pushMatrices();
//            gl::translate( Vec2f(movementX, movementY));
//            gl::drawSolidEllipse( Vec2f( middle.x-eyeSpace , middle.y ), 5, 9);
//            gl::drawSolidEllipse( Vec2f( middle.x+eyeSpace , middle.y ), 5, 9);
//        gl::popMatrices();
//        
//    gl::popMatrices();
    
    // -------------------------------------------    // Dude Nr 3
//    gl::pushMatrices();
//        gl::translate( Vec2f( (middle.x/2)/3, 0) );
//        
//        // Hvíti hringur
//        gl::color(255, 255, 255);
//        gl::drawSolidCircle(middle, radius);
//        
//        //Svarti Hringur
//        
//        gl::lineWidth(15);
//        gl::color(0,0,0);
//        gl::drawStrokedCircle(middle, radius);
//        
//        //Augu
//        
//        gl::pushMatrices();
//    
//        if(sameMirror) {
//            gl::translate( Vec2f(-movement2Spin, movement2));
//        } else {
//            gl::translate( Vec2f(movement2Spin, movement2));
//        }
//    
//        gl::color(0, 0, 0);
//        gl::drawSolidEllipse( Vec2f( middle.x-eyeSpace , middle.y ), 5, 9);
//        gl::color(0, 0, 0);
//        gl::drawSolidEllipse( Vec2f( middle.x+eyeSpace , middle.y ), 5, 9);
//        
//        gl::popMatrices();
//        
//        gl::color( 0, 255, 255 );
//        gl::drawStrokedCircle(middle, radius+4);
//        gl::drawStrokedCircle(middle, radius+6);
//        gl::drawStrokedCircle(middle, radius+8);
//        gl::drawStrokedCircle(middle, radius+10);
//        
//    gl::popMatrices();
    
    for (int i = 0; i < 10; i++) {
        gaur[i].draw();
    }


    
    
}

CINDER_APP_NATIVE( KinkaKolliApp, RendererGl )
