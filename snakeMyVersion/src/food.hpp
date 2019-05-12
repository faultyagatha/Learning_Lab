//
//  food.hpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#ifndef food_hpp
#define food_hpp

#include <stdio.h>
#include "ofMain.h" //need to get an access to openFrameworks

class Food {
public:
    Food();
    
    int size;
    ofVec2f pos;
    ofColor colour;
    ofVec2f getPos() const;
    
//    void setup(float posX, float posY);
    void setup();
    void draw();
    void setNewPos();
};

#endif /* food_hpp */
