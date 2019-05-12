//
//  border.hpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#ifndef border_hpp
#define border_hpp

#include <stdio.h>
#include "ofMain.h" //need to get an access to openFrameworks

class Border {
public:
    Border(); //constructor
    
    //variables
    int top;
    int bottom;
    int left;
    int right;
    
    //functions
    void setup();
    void draw();
//    void checkBorders(ofVector2 snakePos, int snakeSize);
};


#endif /* border_hpp */
