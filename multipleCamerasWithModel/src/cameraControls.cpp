//
//  cameraControls.cpp
//  multipleCamerasWithModel
//
//  Created by Valeriia Barvinska on 16.06.19.
//

#include "cameraControls.hpp"

//constructor
cameraControls::cameraControls() {
    truck =   0.0f;
    roll =  0.0f;
    orbit = 0.0f;
    bOrbit = false;
    bRoll =  false;
    bTruck = false;
    bDolly = false;
    targetDistance = 300.f;
    cam.setPosition(0, 0, 1000);
    cam.lookAt(ofVec3f(0, 0, 0));
}

void cameraControls::cameraOrbit() {
    if (bOrbit) orbit += 0.1f;
    float lat = sin(orbit * M_PI / 180.f) * 90.f;
    ofVec3f centrePoint = ofVec3f(0, 0, 0);
    //orbit node around a global position at a specific radius.
    cam.orbitDeg(orbit, lat, targetDistance, centrePoint);
}

void cameraControls::cameraRoll() {
    if (bRoll) roll += 0.1f;
    //roll left+right relative to current orientation (around local z axis).
    cam.rollDeg(roll);
}

//question: how to resume the position and start on where we finished
void cameraControls::cameraTruck() {
    if (bTruck) {
        truck += 0.1;
    //move sideways (in local x axis).
        cam.truck(truck);
    }
}

//question: how to resume the position and start on where we finished
//answer: create additional status variables
void cameraControls::cameraDolly() {
    if (bDolly) {
        targetDistance += 0.1;
        //move forward+backward (in local z axis).
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
    if (key == 'h') {
    bOrbit = !bOrbit;
    }
    else if (key == 'r') {
    bRoll = !bRoll;
    }
    else if (key == 't') {
        bTruck = !bTruck;
    }
    else if (key == 'd') {
        bDolly = !bDolly;
    }
    else if (key == OF_KEY_UP) {
        //question: how to resume the manual control over the dolly
//        targetDistance += ofLerp(1., 2., 0.1);
        targetDistance += 0.1;
        cam.dolly(targetDistance);
        cout << targetDistance << endl;
    }
    else if (key == OF_KEY_DOWN) {
//        targetDistance -= ofLerp(2., 2.5, 0.1);
        targetDistance *= 0.01;
        cam.dolly(targetDistance);
        cout << targetDistance << endl;
        
    }
    else if (key == OF_KEY_LEFT) {
        cam.truck(truck += 0.1);
        cout << truck << endl;
    }
    else if (key == OF_KEY_RIGHT) {
        cam.truck(truck -= 0.1);
        cout << truck << endl;
    }
}
