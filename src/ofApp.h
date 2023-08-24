#pragma once

#include "ofMain.h"
#include <vector>
#include "Entity.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
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


		//mis variables
		float posx;
		float posy;

		float gravity = 19.81f * 200; //escala a 200 px por metro

		float radioCirculo;

		std::vector<Entity> gameObjects;
		
};