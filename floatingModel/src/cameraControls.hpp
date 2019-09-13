/*
 cameraControls.cpp
 customised camera controls:
 - close-up: change in targetDistance;
 - roll: roll left+right relative to current orientation (around local z axis);
 - orbit: orbit node around a global position at a specific radius;
 - truck: move sideways (in local x axis);
 - dolly: move forward+backward (in local z axis).
 
 author: @faultyagatha
 */

#ifndef cameraControls_hpp
#define cameraControls_hpp

#include <stdio.h>
#include "ofMain.h" // include main to have a reference to the openFrameworks

class cameraControls {
public:
    
    cameraControls(); //default constructor
    float getTargetDistance();
    
    void cameraOrbit();
    void cameraOrbitFast();
    void cameraRoll();
    void cameraPanLeft();
    void cameraPanRight();
    void cameraPanForward();
    void cameraPanBackward();
    void cameraCloseUp();
    void update();
    void draw();
    void cameraBegin();
    void cameraEnd();
    void cameraKeyPressed(int key);
    
private:
    
    ofCamera cam;

    bool bOrbit;
    bool bOrbitFast;
    bool bRoll;
    bool bForward;
    bool bBackward;
    bool bCloseUp;
    bool bPanLeft;
    bool bPanRight;
    
    float roll;
    float orbit;
    float truck;
    float targetDistance;
    float dolly;
    };

#endif /* cameraControls_hpp */
