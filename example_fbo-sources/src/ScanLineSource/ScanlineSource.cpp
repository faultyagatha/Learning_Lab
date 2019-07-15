#include "ScanlineSource.h"
#include <iostream>


//------- modified version (@faulty_agatha)

void ScanlineSource::setup(){
    shader.load("⁨sources⁩/shaders⁩/voronoi1");
    // source name
    name = "Scanline Source";
    allocate(ofGetWidth(), ofGetHeight());
}

// Don't do any drawing here
void ScanlineSource::update(){
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void ScanlineSource::draw(){
        drawShader();
}

void ScanlineSource::drawShader() {
    shader.begin();
    float time = ofGetElapsedTimef();
    float width = ofGetWidth();
    float height = ofGetHeight();
    float resolution[] = {width, height};
    float scale = 2.0;
    float cell_size = 2.0;
    shader.setUniform1f("u_time", time);
    shader.setUniform2fv("u_resolution", resolution);
    shader.setUniform1f("u_scale", scale);
    shader.setUniform1f("u_cell_size", cell_size);
    ofDrawRectangle(0., 0., ofGetWidth(), ofGetHeight());
    shader.end();
}

