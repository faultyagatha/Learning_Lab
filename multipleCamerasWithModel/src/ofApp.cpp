/* using member functions of the ofNode class
 and only one camera for the start
 references:
 https://learnopengl.com/Getting-started/Camera
 https://github.com/andreasmuller/NoiseWorkshop
 press TAB to show the gui and change the colour of the model
 at the moment, there is no possibility to change the shaders on the fly.
 The code must be uncommented in the frag shader.
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //shader load
    shader.load("shaders/LiveCodingSurface/GL2/LiveCodingSurface");
    
    ofSetVerticalSync(true);
    ofBackgroundGradient(ofColor(255), ofColor(128));
    ofEnableSmoothing();
    ofDisableArbTex(); //we want our texture coordinates in 0..1
    
    // load the model
    model.loadModel("models/woman.obj");
    model.setRotation(0, 180, 1, 1, 0);
    
    //light settings
    ofSetSmoothLighting(true);
    light.setPointLight();
    light.setPosition(ofVec3f(2, 10, 2));
    light.enable();
    
    //material setup
    ofSetGlobalAmbientColor(ofColor(20, 20, 20));
    material.setDiffuseColor(ofFloatColor::white);
    material.setSpecularColor(ofFloatColor::white);
    material.setEmissiveColor(ofFloatColor::black);
    material.setAmbientColor(ofFloatColor::black);
    material.setShininess(10);
    
    //gui
    string settingsPath = "Settings/Main.xml";
    gui.setup("Main", settingsPath);
    
    gui.add(color1.set("Color 1", ofColor::white, ofColor(0,0,0,0), ofColor::white));
    gui.add(color2.set("Color 2", ofColor::white, ofColor(0,0,0,0), ofColor::white));
    gui.add(color3.set("Color 3", ofColor::white, ofColor(0,0,0,0), ofColor::white));
    gui.add(shininess.set("shininess",  20.0f,  0.0f,  127.0f));
    
    gui.loadFromFile(settingsPath);
    drawGui = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.cameraOrbit();
    cam.cameraRoll();
    cam.cameraTruck();
    cam.cameraDolly();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0.0);
    //to pass to the shader
    float mx = ofGetMouseX() / (float)ofGetWidth();
    float my = ofGetMouseY() / (float)ofGetHeight();
    
    ofEnableDepthTest();
    
    cam.cameraBegin();
    material.setShininess(shininess);
    material.begin();
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("mouseX", mx);
    shader.setUniform1f("mouseY", my);
    
    // Convert 0..255 colors to 0..1
    ofFloatColor col1 = color1.get();
    ofFloatColor col2 = color2.get();
    ofFloatColor col3 = color3.get();
    
    shader.setUniform4fv("color1", col1.v );
    shader.setUniform4fv("color2", col2.v );
    shader.setUniform4fv("color3", col3.v );
    
    //shader.setUniform1f("shininess", shininess );
    
    ofSetColor(ofColor::white);
    
    ofPushMatrix();
    ofTranslate(345, 10, 0);
//    ofTranslate(mouseX, mouseY, 0);
//    cout << mouseX << endl;
//    cout << mouseY << endl;
//    cout << model.getPosition() << endl;
    model.drawFaces();
    ofPopMatrix();

    shader.end();
    material.end();
    ofDisableLighting();
    ofSetColor(light.getDiffuseColor());
    cam.cameraEnd();
    ofDisableDepthTest();
    
    if(drawGui) gui.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cam.cameraKeyPressed(key);
    
    if(key == OF_KEY_TAB) {
        drawGui = !drawGui;
    }
    else if(key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
