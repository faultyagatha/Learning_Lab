#pragma once

#include "ofMain.h"
#include "FboSource.h"

//------- modified version (@faulty_agatha)
class ScanlineSource : public ofx::piMapper::FboSource {
public:
    void setup();
    void update();
    void draw();
    void drawShader();
    
    ofShader shader;
};
