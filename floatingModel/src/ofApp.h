#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "cameraControls.hpp"
#include "ofxGui.h"
#include "ofxAutoReloadedShader.h" 
#include "ofxSyphon.h"
#include "ofxOsc.h"


//send port
#define PORT 1234


class ofApp : public ofBaseApp{

	public:
		void setup();
        void syphonSetup();
		void update();
        void setUniforms();
    
        void draw();
        void drawMode(int key);
        void loadShaders(size_t which);
        void error(std::string s);
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
private:
    cameraControls cam;
    ofxAssimpModelLoader model;
    bool drawVerts;
    bool drawWire;
    bool drawFaces;
    
    ofxAutoReloadedShader shader;
    //gui shader
    ofxPanel gui;
    ofParameter<float> cell_size;
    ofParameter<float> scale;
    ofParameter<float> amp;
    ofParameter<float> freq;
    bool drawGui;
    
    ofxOscReceiver receiver;
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonClient mClient;
   
};


