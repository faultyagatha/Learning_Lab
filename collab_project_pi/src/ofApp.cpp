/*
 Shader layout desigend for the projection mapping with raspberry pi (optimised for GLES)
 To do:
 - bild on raspberry pi with ofxPiMapper
 - optional: add osc
 - bind the parameters of a shader to osc
 
 Author: @faulty_agatha
 Last modified: 5.07.2019
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("voronoi1"); //voronoi1 is adapted for GLES
//    shader.load("voronoi2"); //voronoi2 and voronoi3 are #version 120 and can run in oF independently of raspberry pi settings
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
    
    //pass the uniforms to the shaders (scale and cell_size are for the OSC implementation)
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2fv("u_resolution", resolution);
    shader.setUniform1f("u_scale", scale);
    shader.setUniform1f("u_cell_size", cell_size);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
