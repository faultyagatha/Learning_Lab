#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(50);
    snake.setup();
    border.setup();
//    food.setup(grid.cols, grid.rows);
    food.setup();
    grid.calculateLocation(snake.elementSize);
}

//--------------------------------------------------------------
void ofApp::update(){
    snake.update();
//    snake.checkBorders(border.left, border.right, border.top, border.bottom);
    checkBorders();
    if (snake.eat(food.getPos())) {
        food.setNewPos();
    }
//    border.checkBorders(snake.pos, snake.size);
}

//--------------------------------------------------------------
void ofApp::checkBorders() {
//    cout << "checking borders" <<;
//    ofClamp(snake.pos.x, border.left + snake.size, border.right - snake.size);
//    ofClamp(snake.pos.y, border.top + snake.size, border.bottom - snake.size);

//    //todo: rewrite it using switch statement
    int xPos = static_cast<int>(snake.elementPos.x);
    
    if(xPos + snake.elementSize >= border.right) {
        snake.setDirection(-1, 0);
    } else if(snake.elementPos.y + snake.elementSize <= border.top) {
        snake.setDirection(0, 1);
    } else if(snake.elementPos.x + snake.elementSize <= border.left) {
        snake.setDirection(1, 0);
    } else if(snake.elementPos.y + snake.elementSize >= border.bottom) {
        snake.setDirection(0, -1);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(100, 150, 180);
    border.draw();
    snake.draw();
    food.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //todo: how to optimise this part?
    if (key == OF_KEY_RIGHT) {
        snake.setDirection(1, 0);
    } else if (key == OF_KEY_LEFT) {
        snake.setDirection(-1, 0);
    } else if (key == OF_KEY_UP) {
        snake.setDirection(0, -1);
    } else if (key == OF_KEY_DOWN) {
        snake.setDirection(0, 1);
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
