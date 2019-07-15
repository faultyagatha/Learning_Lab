#include "ofMain.h"
#include "ofApp.h"

int main(){
    //to make shader work on raspberry pi:
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.setSize(1280, 720);
    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());
}
