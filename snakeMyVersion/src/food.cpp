//
//  food.cpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#include "food.hpp"

Food::Food() {
    
}

//attempt to implement the grid idea, doesn't work

//void Food::setup(float posX, float posY) {
//    pos.set(floor(ofRandom(posX)), floor(ofRandom(posY)));
//    size = 25;
//}

void Food::setup() {
    pos.set(ofRandom(ofGetWidth()/4), ofRandom(ofGetHeight()/4));
    size = 25;
}

void Food::draw() {
    colour.set(ofRandom(255),ofRandom(255),ofRandom(255));
    ofDrawRectangle(pos.x, pos.y, size, size);
}

void Food::setNewPos() {
          pos.set(ofRandom(ofGetWidth() - 15)),
          pos.set(ofRandom(ofGetHeight() - 15));
}

ofVec2f Food::getPos() const {
    
    return pos;
}



