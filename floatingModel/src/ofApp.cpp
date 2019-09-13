/* a simple application that
 - loads a 3d model;
 - allows for various modes of drawing the model's mesh;
 - has a customised camera control (close-up, pan back, orbit, etc);
 - implements 5 fragment shaders with possibility to switch between them on key pressed
 - and 1 simple vertex shader that displaces model's vertices;
 - GUI for a smoother shader control;
 - additionally: syphon integration
 
 references:
 https://github.com/hamoid/Fun-Programming/wiki/In-the-Mood-for-Shaders
 https://github.com/andreasmuller/NoiseWorkshop
 https://learnopengl.com/Getting-started/Camera
 
 https://thebookofshaders.com
 http://iquilezles.org
 
 *********************************************
 INSTRUCTIONS:
 - use keys 0-5 to switch between shaders
 - press TAB to show the gui
 - use keys 'h', 'r', 't', 'd'
    and     'key down', '-up', '-left', and '-right'
    for camera manipulations
 - use keys  'w', 'f', 'v'
    for switching between drawing modes of a model
 
 author: @faultyagatha
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    loadShaders(0);
    
    ofSetVerticalSync(true);
    ofBackgroundGradient(ofColor(255), ofColor(128));
    ofEnableSmoothing();
    ofDisableArbTex(); //we want our texture coordinates in 0..1
    
    model.loadModel("models/womanRobot_norig.obj");
    model.setRotation(0, 180, 1, 1, 0);
    drawFaces = false;
    drawVerts = true;
    drawWire = false;
    
    ofSetSmoothLighting(true);
    light.setPointLight();
    light.setPosition(ofVec3f(2, 10, 2));
    light.enable();
    
    //gui for shaders
    string settingsPath = "Settings/Main.xml";
    gui.setup("Main", settingsPath);
    gui.add(cell_size.set("cell_size",  2.0f,  0.1f,  30.0f));
    gui.add(scale.set("scale",  2.0f,  0.5f,  10.0f));
    gui.loadFromFile(settingsPath);
    drawGui = false;
    
//    syphonSetup();
}

void ofApp::syphonSetup() {
    ofSetWindowTitle("ofxSyphon Example");
    mainOutputSyphonServer.setName("Screen Output");
    mClient.setup();
    mClient.set("","Simple Server");
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast.
}

//--------------------------------------------------------------
void ofApp::update() {
    cam.cameraOrbit();
    cam.cameraOrbitFast();
    cam.cameraRoll();
    cam.cameraPanLeft();
    cam.cameraPanRight();
    cam.cameraPanForward();
    cam.cameraPanBackward();
    cam.cameraCloseUp();
}

void ofApp::setUniforms() {
    float width = ofGetWidth();
    float height = ofGetHeight();
    float resolution[] = {width, height};
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform1f("u_mouse_x", ofGetMouseX()); //test
    shader.setUniform2fv("u_resolution", resolution);
    shader.setUniform1f("u_scale", scale);
    shader.setUniform1f("u_cell_size", cell_size);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetBackgroundColor(0.0);
    ofEnableDepthTest();
    cam.cameraBegin();
    shader.begin();
    setUniforms();
    
    ofSetColor(ofColor::white);
    
    ofPushMatrix();
    ofTranslate(345, 10, 0);
    
    if(drawVerts) model.drawVertices();
    else if(drawWire) model.drawWireframe();
    else if(drawFaces)model.drawFaces();

    ofPopMatrix();

    shader.end();
    ofDisableLighting();
    ofSetColor(light.getDiffuseColor());
    cam.cameraEnd();
    ofDisableDepthTest();
    
    if(drawGui) gui.draw();
    
    //Syphon stuff
//    mClient.draw(50, 50);
//    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::drawMode(int key) {
    switch(key) {
        case 'w':
            drawVerts = false;
            drawWire = true;
            drawFaces = false;
            ofLog() << "wireframe mode";
            break;
        case 'f':
            drawVerts = false;
            drawWire = false;
            drawFaces = true;
            ofLog() << "faces mode";
            break;
        case 'v':
            drawVerts = true;
            drawWire = false;
            drawFaces = false;
            ofLog() << "vertices mode";
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::loadShaders(size_t which) {
    std::vector<std::string> filenames {
        "distanceFields",
        "meshDeform",
        "simplexNoise1",
        "voronoi1",
        "voronoi2",
        "worley"
    };
    try {
        auto filename = filenames[which];
        shader.load(filename);
        ofLog() << "Shader " << filename << " loaded at frame #" << ofGetFrameNum();
    }
    catch(std::exception& e) {
        std::cerr << "Error" <<e.what();
        return 1; //todo: check with stan if it's right
    }
}

//--------------------------------------------------------------
void ofApp::error(std::string s) {
    throw std::runtime_error(s);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    cam.cameraKeyPressed(key);
    drawMode(key);
    
    if(key == OF_KEY_TAB) drawGui = !drawGui;
    else if(key == 'p') ofToggleFullscreen();
    else if(key >= '0' && key <= '5') loadShaders(static_cast<size_t>(key - '0'));
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
