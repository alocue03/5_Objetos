#pragma once

#include "ofMain.h"
#include <vector>
#include "Entity.h"
#include "ofxGui.h"
#include <list> //std::list lista ligada

class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupPelotas();
		void setupLemmings();
		void update();
		void updatePelotas();
		void updateLemmings();

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

		float gravity = 9.81f * 100; //escala a 100 px por metro

		float radioCirculo;

		std::vector<Entity> gameObjects;

		//imagen de fondo
		ofImage imgHogar;

		//estados de la aplicacion
		enum EAppState { menu, pelotas, lemmings, max }appstate;

		ofTrueTypeFont titleFont;
		ofTrueTypeFont uiFont;
		//cosas del ui
		ofxPanel mainmenu;
		ofxButton btnEjercicio1, btnEjercicio2;
		
		void onBtn1Pressed();
		void onBtn2Pressed();

		//juego con inventario (Lemmings)
		ofImage playerSrpiteImg;
		float posx;
		float posy;
		ofVec2f playerSize;
		ofVec2f playerSpriteOffset;
		bool w, a, s, d;
		//inventario, es una lista ligada
		std::list<Entity> inventory;
		void NextItem();
		void PrevItem();
		std::list<Entity>::iterator inventoryIterator;

};
