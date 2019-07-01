/*
 a base for the projection mapping:
 - add a simple shader
 - add osc
 - bind the parameters of a shader to osc
 - bild on raspberry pi
 - optional: add more shaders
 
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    loadShaders(0);
    shader.load("voronoi1"); //load both shaders simult
//    shader.load("voronoi2");
//    shader.load("voronoi3");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    setUniforms();
    ofDrawRectangle(0., 0., ofGetWidth(), ofGetHeight());
    shader.end();
}

//--------------------------------------------------------------
void ofApp::setUniforms(){
    float width = ofGetWidth();
    float height = ofGetHeight();
    float resolution[] = {width, height};
    float time = ofGetElapsedTimef();
    float scale = 2.0;
    float cell_size = 2.0;
    
    //pass the time and resolution
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2fv("u_resolution", resolution);
    shader.setUniform1f("u_scale", scale);
    shader.setUniform1f("u_cell_size", cell_size);

    
}

//--------------------------------------------------------------
//void ofApp::loadShaders(size_t which) {
//    std::vector<std::string> filenames {
//        "00_flat",
//        "01_gradient",
//        "02_wave",
//        "03_uniform"
//    };
//    auto filename = filenames[which]; //todo: make the programe throw the exception if out of bounds but without termination
//    filename += "_GL3";
//
////#ifdef TARGET_OPENGLES
////    filename += "_ES2";
////#else
////    if(ofIsGLProgrammableRenderer()) {
////        filename += "_GL3";
////    } else {
////        filename += "_GL2";
////    }
////#endif
//    shader.load(filename);
//
//    ofLog() << "Shader " << filename << " loaded at frame #" << ofGetFrameNum();
//}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key >= '0' && key <= '4') {
//        loadShaders(static_cast<size_t>(key - '0'));
//    }
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
