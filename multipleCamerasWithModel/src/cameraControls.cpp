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

#include "cameraControls.hpp"

//constructor
cameraControls::cameraControls()
    : truck {0.0}, roll {0.0}, orbit {0.0},
    bOrbit{false}, bRoll {false}, bTruck {false}, bDolly {false},
    targetDistance {300.} {
        cam.setPosition(0, 0, 1000);
        cam.lookAt(ofVec3f{0, 0, 0});
}

void cameraControls::cameraOrbit() {
    if (bOrbit) orbit += 0.1;
    float lat = sin(orbit * M_PI / 180.) * 90.;
    ofVec3f centrePoint = ofVec3f(0, 0, 0);
    cam.orbitDeg(orbit, lat, targetDistance, centrePoint);
}

void cameraControls::cameraRoll() {
    if (bRoll) roll += 0.1;
    cam.rollDeg(roll);
}

//question: how to resume the position and start on where we finished
void cameraControls::cameraTruck() {
    if (bTruck) {
        truck += 0.1;
        cam.truck(truck);
        cout << "truck: " << truck;
    }
}

//question: how to resume the position and start on where we finished
//answer: create additional status variables
void cameraControls::cameraDolly() {
    if (bDolly) {
        targetDistance += 0.1;
        cam.dolly(targetDistance);
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
        case 'h':
            bOrbit = !bOrbit;
            break;
        case 'r':
            bRoll = !bRoll;
            break;
        case 't':
            bTruck = !bTruck;
            break;
        case 'd':
            bDolly = !bDolly;
            break;
        case OF_KEY_UP:
        //question: how to resume the manual control over the dolly
//        targetDistance += ofLerp(1., 2., 0.1);
            targetDistance += 0.1;
            cam.dolly(targetDistance);
            cout << targetDistance << endl;
            break;
        case OF_KEY_DOWN:
//        targetDistance -= ofLerp(2., 2.5, 0.1);
            targetDistance *= 0.01;
            cam.dolly(targetDistance);
            cout << targetDistance << endl;
            break;
        case OF_KEY_LEFT:
            cam.truck(truck += 0.1);
            cout << truck << endl;
            break;
        case OF_KEY_RIGHT:
            cam.truck(truck -= 0.1);
            cout << truck << endl;
            break;
        default:
            break;
    }
}
