#pragma once

#include "ofMain.h"
#include <vector>
#include "Entity.h"
#include "ofxGui.h"
#include <list> //std::list lista ligada

struct ItemSpawn {
	Entity itemsEntities; 
	float spawnTime; 
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupPelotas();
		void setupLemmings();
		void update();
		void updatePelotas();
		void updateLemmings();
		void draw();

		void SpawnItem();


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
		std::list<ItemSpawn> activeItems;


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

		Entity* currentItem;

		int animationnumber = 0;
		float animationchange = 0.0f;
		float animationFast = 6.5f;
		char ultDire = 0;

		int weaponIndex = 0;
		int weaponMin = 0;
		int weaponMax = 2;
		float lastSpawnTime;

		Entity lance;
		Entity flail;
		Entity olympia;

		//void NextItem();
		//void PrevItem();

};
