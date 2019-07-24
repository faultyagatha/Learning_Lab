//
//  cameraControls.hpp
//  multipleCamerasWithModel
//
//  Created by Valeriia Barvinska on 16.06.19.
//

#ifndef cameraControls_hpp
#define cameraControls_hpp

#include <stdio.h>
#include "ofMain.h" // include main to have a reference to the openFrameworks #include "ofApp.h"

//think what goes into private

class cameraControls {
public:
    
    cameraControls();

    ofCamera cam;
    bool bOrbit;
    bool bRoll;
    bool bTruck;
    bool bDolly;
    float roll;
    float orbit;
    float truck;
    float targetDistance;
    
    void cameraOrbit();
    void cameraRoll();
    void cameraTruck();
    void cameraDolly();
    void update();
    void draw();
    void cameraBegin();
    void cameraEnd();
    void cameraKeyPressed(int key);
    
    };


#endif /* cameraControls_hpp */
