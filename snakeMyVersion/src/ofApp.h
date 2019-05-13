#pragma once

#include "ofMain.h"
#include "snake.hpp"
#include "border.hpp"
#include "food.hpp"
#include "grid.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void checkBorders();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    Snake snake;
    Border border;
    Food food;
    Grid grid;
		
};
