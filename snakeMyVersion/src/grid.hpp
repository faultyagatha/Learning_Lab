//
//  grid.hpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include "ofMain.h"
#include "snake.hpp"
#include "food.hpp"

class Grid {
public:
    Grid(); //constructor
    int cols;
    int rows;
    
    void calculateLocation(int pixel_size); //size of the grid slot, and hence the size of the snake
};

#endif /* grid_hpp */
