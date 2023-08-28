#include "ofApp.h"

void ofApp::onBtn1Pressed()
{
	std::cout << "boton 1 \n";
	appstate = EAppState::pelotas;
	setupPelotas();
}

void ofApp::onBtn2Pressed()
{
	std::cout << "boton 2 \n";
	appstate = EAppState::lemmings;
	setupLemmings();
}
//--------------------------------------------------------------
void ofApp::setup(){
	//Establecer el primer estado de la app
	appstate = EAppState::menu;

	titleFont.load("MyFont.ttf", 24);
	uiFont.load("MyFont.ttf", 12);

	mainmenu.setup();
	mainmenu.add(btnEjercicio1.setup("Pelotas rebotando"));
	mainmenu.add(btnEjercicio2.setup("Tipo Lemmings"));
	mainmenu.setPosition(ofGetWidth() / 2 - mainmenu.getWidth() / 2,
						ofGetHeight() / 2 - mainmenu.getHeight() / 2);
	btnEjercicio1.addListener(this, &ofApp::onBtn1Pressed);
	btnEjercicio2.addListener(this, &ofApp::onBtn2Pressed);

}

void ofApp::setupPelotas()
{
	Entity e = Entity();
	e.position->x = 100;
	e.position->y = 100;
	e.Velocity->x = 50;
	gameObjects.push_back(Entity(e));

	Entity e2 = Entity();
	e2.position->x = 200;
	e2.position->y = 200;
	e2.Velocity->x = 50;
	gameObjects.push_back(Entity(e2));
	std::cout << gameObjects.size() << "\n";
	imgHogar.load("house.png");
}

void ofApp::setupLemmings()
{
	posx = 0;
	posy = 0;
	radioCirculo = 25;
	playerSrpiteImg.load("Player.png");
	//tamaño del jugador
	playerSize = ofVec2f(171, 233);
	playerSpriteOffset = ofVec2f(290, 273);
	//inventory
	Entity hands = Entity();
	hands.name = "Manos";
	inventory.push_back(hands);
	Entity Espada = Entity();
	Espada.name = "Espada";
	inventory.push_back(Espada);
	Entity Halbred = Entity();
	Halbred.name = "Halbred";
	inventory.push_back(Halbred);

	currItem = &hands;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (appstate == EAppState::pelotas)
	{
		updatePelotas();
	}
	else if (appstate == EAppState::menu)
	{

	}
	else if (appstate == EAppState::lemmings)
	{
		updateLemmings();
	}

}

void ofApp::updatePelotas()
{
	//mover entidades
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//aplicar la aceleracion de la gravedad en el espacio
		gameObjects[i].Velocity->y += gravity * ofGetLastFrameTime();

		//colision / rebote con el piso/paredes
		if (gameObjects[i].position->y >= ofGetHeight())
		{
			gameObjects[i].position->y = ofGetHeight();
			gameObjects[i].Velocity->y *= -1;
		}
		if (gameObjects[i].position->x >= ofGetWidth())
		{
			gameObjects[i].position->x = ofGetWidth();
			gameObjects[i].Velocity->x *= -1;
		}
		//aplicar velocidad como posicion
		gameObjects[i].position->x += gameObjects[i].Velocity->x * ofGetLastFrameTime();
		gameObjects[i].position->y += gameObjects[i].Velocity->y * ofGetLastFrameTime();

	}
}

void ofApp::updateLemmings()
{
	//mover el sprite dependiendo de los inputs
	if (w)
	{
		posy -= 200 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(300, 18);
		playerSize = ofVec2f(160, 233);
	}
	if (s)
	{
		posy += 200 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(290, 273);
		playerSize = ofVec2f(171, 233);
	}
	if (a)
	{
		posx -= 200 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(59, 270);
		playerSize = ofVec2f(146, 232);
	}
	if (d)
	{
		posx += 200 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(560, 273);
		playerSize = ofVec2f(146, 232);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (appstate == EAppState::pelotas)
	{
		ofSetColor(ofColor::white);
		ofBackground(ofColor::darkCyan);
		imgHogar.draw(200, ofGetHeight() - imgHogar.getHeight());

		ofSetColor(240, 12, 12);

		if (gameObjects.size() > 0)
		{
			for (int i = 0; i < gameObjects.size(); i++)
				gameObjects[i].draw();
		}
	}
	else if (appstate == EAppState::menu)
	{
		ofBackground(ofColor::blueViolet);
		mainmenu.draw();
	}
	else if (appstate == EAppState::lemmings)
	{
		ofBackground(ofColor::darkRed);
		ofSetColor(0, 0, 0);
		titleFont.drawString("what do the numbers mean? mason", 100, 100);
		ofSetColor(255, 255, 255);
		//ofCircle(posx, posy, radioCirculo);
		//playerSrpiteImg.draw(posx,posy);
		playerSrpiteImg.drawSubsection(posx, posy, playerSize.x, 
			playerSize.y, playerSpriteOffset.x, 
			playerSpriteOffset.y);
		//poner el nombre del item actual
		ofSetColor(255, 255, 0);
		titleFont.drawString(currItem->name, posx, posy);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'w') w = true;
	if (key == 'a') a = true;
	if (key == 's') s = true;
	if (key == 'd') d = true;

	if (appstate == EAppState::lemmings)
	{
		if (key == 57357)
		{
			std::cout << "item anterior" << key << "\n";
		}
		if (key == 57359)
		{
			std::cout << "item que sigue" << key << "\n";
		}
	}
}
	

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'w') w = false;
	if (key == 'a') a = false;
	if (key == 's') s = false;
	if (key == 'd') d = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (x >= 0 && y >= 0 && x <= ofGetWidth() && y <= ofGetHeight()) {
		Entity newEntity = Entity();
		newEntity.position->x = x;
		newEntity.position->y = y;
		newEntity.Velocity-> x= 70;
		newEntity.entityColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
		gameObjects.push_back(newEntity);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
