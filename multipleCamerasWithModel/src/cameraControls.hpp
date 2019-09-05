/*
 cameraControls.cpp
 customised camera control:
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
    
    cameraControls();
    
    void cameraOrbit();
    void cameraRoll();
    void cameraTruck();
    void cameraDolly();
    void update();
    void draw();
    void cameraBegin();
    void cameraEnd();
    void cameraKeyPressed(int key);
    
private:
    ofCamera cam;
    //TODO: maybe I could use struct for this?
    bool bOrbit;
    bool bRoll;
    bool bTruck;
    bool bDolly;
    float roll;
    float orbit;
    float truck;
    float targetDistance;
    };


#endif /* cameraControls_hpp */
