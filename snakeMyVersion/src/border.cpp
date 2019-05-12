//
//  border.cpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#include "border.hpp"

Border::Border() {
    
}

void Border::setup() {
    top = 10;
    bottom = ofGetHeight()-10;
    left = 10;
    right = ofGetWidth()-10;
}

void Border::draw() {
        ofSetColor(255);
        ofDrawLine(left, top, left, bottom);
        ofDrawLine(right, top, right, bottom);
        ofDrawLine(left, top, right, top);
        ofDrawLine(left, bottom, right, bottom);
}

//void Border::checkBorders(ofVector2 snakePos, int snakeSize) {
//    ofClamp(snakePos.x, left + snakeSize, right - snakeSize);
//    ofClamp(snakePos.y, top + snakeSize, bottom - snakeSize);
//}

