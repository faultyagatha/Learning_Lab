//
//  snake.hpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#ifndef snake_hpp
#define snake_hpp

#include <stdio.h>
#include "ofMain.h" //need to get an access to openFrameworks

class Snake {
public:
    Snake(); //constructor
    
    //variables
    int elementSize;
    ofVec2f elementPos;
    ofVec2f speed;
    float speedFactor;
    ofColor elementColour;
    std::vector<ofVec2f> snakeElements;
    
    void setup();
    void setDirection(float x, float y);
    void checkBorders(int leftBorder, int rightBorder, int topBorder, int bottomBorder);
    void update();
    void draw();
    
    bool eat(ofVec2f foodPos);
};

#endif /* snake_hpp */
