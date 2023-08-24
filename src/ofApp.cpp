#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	posx = 0;
	posy = 0;
	radioCirculo = 50;
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


}

//--------------------------------------------------------------
void ofApp::update(){

	//mover entidades
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//aplicar la aceleracion de la gravedad en el espacio
		gameObjects[i].Velocity->y = gravity * ofGetLastFrameTime();

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

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::darkCyan);

	ofSetColor(240, 12, 12);
	ofCircle(posx, posy, radioCirculo);

	if (gameObjects.size() > 0)
	{
		for (int i = 0; i < gameObjects.size(); i++)
			gameObjects[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	posx = x;
	posy = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (x >= 0 && y >= 0 && x <= ofGetWidth() && y <= ofGetHeight())
	{
		Entity newEntity = Entity();
		newEntity.position->x = x;
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
