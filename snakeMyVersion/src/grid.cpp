//
//  grid.cpp
//  snakeMyVersion
//
//  Created by Valeriia Barvinska on 12.05.19.
//

#include "grid.hpp"

Grid::Grid() {
    
}

void Grid::calculateLocation(int pixel_size) {
    cols = floor(ofGetWidth()/pixel_size);
    rows = floor(ofGetHeight()/pixel_size);
}
