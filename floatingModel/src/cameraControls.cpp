/*
 cameraControls.cpp
 customised camera controls:
 - roll: roll left+right relative to current orientation (around local z axis);
 - orbit: orbit node around a global position at a specific radius;
 - truck: move sideways (in local x axis);
 - dolly: move forward+backward (in local z axis).

  author: @faultyagatha
*/

#include "cameraControls.hpp"

//constructor
cameraControls::cameraControls()
    : truck{0.0}, roll{0.0}, orbit{0.0}, dolly{0.0},
    bOrbit{false}, bOrbitFast{false},bRoll{false}, bPanLeft{false},
    bPanRight{false}, bForward{false}, bBackward{false},
    targetDistance{300.} {
        cam.setPosition(0, 0, 1000);
        cam.lookAt(ofVec3f{0, 0, 0});
}

void cameraControls::cameraOrbit() {
    if(bOrbit) orbit += 0.1;
    float lat = sin(orbit * M_PI / 180.) * 90.;
    ofVec3f centrePoint = ofVec3f(0, 0, 0);
    cam.orbitDeg(orbit, lat, targetDistance, centrePoint);
}

void cameraControls::cameraOrbitFast() {
    if(bOrbitFast) {
        orbit += 0.4;
        float lat = sin(orbit * M_PI / 180.) * 90.;
        ofVec3f centrePoint = ofVec3f(0, 0, 0);
        cam.orbitDeg(orbit, lat, targetDistance, centrePoint);
    }
}

void cameraControls::cameraRoll() {
    if(bRoll) roll += 0.1;
    cam.rollDeg(roll);
}

void cameraControls::cameraPanLeft() {
    if(bPanLeft) {
        truck += 0.4;
        cam.truck(truck);
        cout << "Pan left: " << truck << "\n";
    }
}

void cameraControls::cameraPanRight() {
    if(bPanRight) {
        truck -= 0.4;
        cam.truck(truck);
        cout << "Pan right : " << truck << "\n";
    }
}

void cameraControls::cameraPanForward() {
    if(bForward) {
        dolly -= 0.4;
        cam.dolly(dolly);
        cout << "panning forward at dolly " << dolly << "\n";
    }
}

void cameraControls::cameraPanBackward() {
    if(bBackward) {
        targetDistance += 0.4;
        cam.dolly(targetDistance);
        cout << "panning backward at the target distance " << targetDistance << "\n";
    }
}

void cameraControls::cameraBegin() {
    cam.begin();
}

void cameraControls::cameraEnd() {
    cam.end();
}

void cameraControls::cameraKeyPressed(int key) {
    switch(key) {
        case 'o':
            bOrbit = !bOrbit;
            break;
        case 'r':
            bRoll = !bRoll;
            break;
        case 'b':
            bOrbitFast = !bOrbitFast;
            break;
        case OF_KEY_LEFT:
            if(bPanRight) bPanRight = false;
            bPanLeft = !bPanLeft;
            break;
        case OF_KEY_RIGHT:
            if(bPanLeft) bPanLeft = false;
            bPanRight = !bPanRight;
            break;
        case OF_KEY_UP:
            if(bBackward) bBackward = false;
            bForward = !bForward;
            break;
        case OF_KEY_DOWN:
            if(bForward) bForward = false;
            bBackward = !bBackward;
            break;
        default:
            break;
    }
}
