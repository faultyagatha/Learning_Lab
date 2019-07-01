#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//    ofSetupOpenGL(1280,720,OF_WINDOW);            // <-------- setup the GL context
    
    //to make shader work on raspberry pi
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.setSize(1280, 720);
    ofCreateWindow(settings);

    ofRunApp(new ofApp());
}
