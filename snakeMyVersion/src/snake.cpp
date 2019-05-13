//
//  snake.cpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#include "snake.hpp"

//constructor
Snake::Snake() {
    
}

void Snake::setup() {
    elementPos.set(ofGetWidth()/2, ofGetHeight()/2);
    speed.set(1, 0); //by default snake will move to the right horisontally
    elementSize = 25;
    elementColour.set(ofRandom(255),ofRandom(255),ofRandom(255)); //random colour
    speedFactor = ofRandom(1., 2.); //todo: change the speed when the snake grows
    
    snakeElements = {};
    // adding first element to the vector
    snakeElements.push_back(ofVec2f{elementPos.x,elementPos.y});
}

void Snake::setDirection(float m_x, float m_y) {
    speed.set(m_x, m_y); //change speed according to the user input values
}

void Snake::checkBorders(int leftBorder, int rightBorder, int topBorder, int bottomBorder) {
        cout << "checking borders" <<
    //todo: take into account the future change in size
    //
        ofClamp(elementPos.x, leftBorder + elementSize, rightBorder - elementSize);
        ofClamp(elementPos.y, topBorder + elementSize, bottomBorder - elementSize);
}

void Snake::update() {
    for (ofVec2f& elementPos : snakeElements) {
        ofVec2f test = elementPos + elementSize;
        elementPos = elementPos + (elementSize * speed);
    }
}

void Snake::draw() {
    for (ofVec2f& elementPos : snakeElements) {
        ofSetColor(elementColour);
        ofDrawRectangle(elementPos.x, elementPos.y, elementSize, elementSize);
    }
}

bool Snake::eat(ofVec2f foodPos) {
    assert(!snakeElements.empty()); //if the vector is not empty, proceed; if it is empy, abort
    
    auto elementPos = snakeElements.front(); //retrieve first element from the vector
    
    if (elementPos.distance(foodPos) <= 0.25) {
        std::cout << " eat!" << std::endl;
        foodPos += elementSize;
        snakeElements.push_back(foodPos);
        return true;
    }
    return false;
}

