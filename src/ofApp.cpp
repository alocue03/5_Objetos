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
	posx = 50;
	posy = 50;
	radioCirculo = 25;
	//cargar el jugador
	playerSrpiteImg.load("Player1.png");
	//tamaño del jugador
	playerSize = ofVec2f(195, 243);
	playerSpriteOffset = ofVec2f(10, 23);
	//inventory
	Entity hands = Entity();
	hands.name = "Manos";
	hands.sprite.load("");
	inventory.push_back(hands);
	Entity Espada = Entity();
	Espada.name = "Espada";
	Espada.sprite.load("Espada.png");
	inventory.push_back(Espada);
	Entity Halbred = Entity();
	Halbred.name = "Halbred";
	Halbred.sprite.load("halbred.png");
	inventory.push_back(Halbred);
	currentItem = &hands;


	//inventoryIterator = inventory.begin(); //inicializar le iterador
	//currItem = &inventory.back();  //back obtiene el ultimo item
	//std::cout << "begin: " << (*inventoryIterator).name << "\n";

	lance.sprite.load("Lance.png");
	lance.name = "Lanza";

	flail.sprite.load("Flail.png");
	flail.name = "Flail";

	olympia.sprite.load("Olympia.png");
	olympia.name = "Olympia gang";

	lastSpawnTime = ofGetElapsedTimef();

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
		if (ultDire != 'w') {
			animationnumber = 0;
			ultDire = 'w';
		}
		posy -= 200 * ofGetLastFrameTime();
		switch ((int)animationnumber) {
		case 0: playerSpriteOffset = ofVec2f(10, 294); break;
		case 1: playerSpriteOffset = ofVec2f(254, 294); break;
		case 2: playerSpriteOffset = ofVec2f(523, 294); break;
		}
	}
	if (s)
	{
		if (ultDire != 's') 
		{
			animationnumber = 0;
			ultDire = 's';
		}
		posy += 200 * ofGetLastFrameTime();
		switch ((int)animationnumber) {
		case 0: playerSpriteOffset = ofVec2f(10, 23); break;
		case 1: playerSpriteOffset = ofVec2f(253, 23); break;
		case 2: playerSpriteOffset = ofVec2f(502, 23); break;
		}
	}
	if (a)
	{
		if (ultDire != 'a') 
		{
			animationnumber = 0;
			ultDire = 'a';
		}
		posx -= 200 * ofGetLastFrameTime();
		switch ((int)animationnumber) {
		case 0: playerSpriteOffset = ofVec2f(10, 581); break;
		case 1: playerSpriteOffset = ofVec2f(262, 581); break;
		case 2: playerSpriteOffset = ofVec2f(509, 581); break;
		}
	}
	if (d)
	{
		if (ultDire != 'd') 
		{
			animationnumber = 0;
			ultDire = 'd';
		}
		posx += 200 * ofGetLastFrameTime();
		switch ((int)animationnumber) {
		case 0: playerSpriteOffset = ofVec2f(46, 863); break;
		case 1: playerSpriteOffset = ofVec2f(286, 863); break;
		case 2: playerSpriteOffset = ofVec2f(530, 863); break;
		}
	}

	if (w ^ a ^ s ^ d)
		animationchange += animationFast * ofGetLastFrameTime();
	if (animationchange >= 3) 
		animationchange = 0;
	if (animationchange > 0 && animationchange < 1)
		animationnumber = 0;
	if (animationchange > 1 && animationchange < 2)
		animationnumber = 1;
	if (animationchange > 2 && animationchange < 3)
		animationnumber = 2;
	if (animationchange >= 3)
		animationnumber = 3;

	if (animationnumber >= 3) animationnumber = 0;

	if (weaponIndex < weaponMin)
		weaponIndex = weaponMax;
	if (weaponIndex > weaponMax)
		weaponIndex = weaponMin;

	std::list<Entity>::iterator it = inventory.begin();
	if (weaponIndex == 0 && it != inventory.end()) {
		currentItem = &(*it);
	}
	else if (weaponIndex == 1 && std::next(it) != inventory.end()) {
		currentItem = &(*std::next(it));
	}
	else if (weaponIndex == 2 && std::next(it, 2) != inventory.end()) {
		currentItem = &(*std::next(it, 2));
	}
	else if (weaponIndex == 3 && std::next(it, 3) != inventory.end()) {
		currentItem = &(*std::next(it, 3));
	}
	else if (weaponIndex == 4 && std::next(it, 4) != inventory.end()) {
		currentItem = &(*std::next(it, 4));
	}
	else if (weaponIndex == 5 && std::next(it, 5) != inventory.end()) {
		currentItem = &(*std::next(it, 5));
	}

	float currentTime = ofGetElapsedTimef();
	float spawnInterval = 5.0f;

	if (currentTime - lastSpawnTime > spawnInterval) {
		SpawnItem();
		lastSpawnTime = currentTime;
	}

	for (auto it = activeItems.begin(); it != activeItems.end(); ) {
		if (currentTime >= it->spawnTime) {
			float distance = ofDist(it->itemsEntities.posX, it->itemsEntities.posY, posx, posy);
			if (distance < radioCirculo) {
				inventory.push_back(it->itemsEntities);
				if (weaponMax < 6)
					weaponMax++;
				it = activeItems.erase(it);
			}
			else {
				++it;
			}
		}
		else {
			++it;
		}
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
		playerSrpiteImg.drawSubsection(posx, posy, playerSize.x, 
			playerSize.y, playerSpriteOffset.x, 
			playerSpriteOffset.y);
		titleFont.drawString(currentItem == nullptr ? "NULL" : currentItem->name.c_str(), posx, posy);
		if (currentItem && currentItem->sprite.isAllocated())
			currentItem->sprite.draw(posx + 25, posy);
		for (auto& itemSpawn : activeItems) {
			float currentTime = ofGetElapsedTimef();
			if (currentTime >= itemSpawn.spawnTime) {
				itemSpawn.itemsEntities.sprite.draw(itemSpawn.itemsEntities.posX, itemSpawn.itemsEntities.posY);
			}
		}
	}
}
void ofApp::SpawnItem()
{
	std::vector<Entity> items = { lance, flail, olympia };

	int randomIndex = ofRandom(items.size());
	Entity selectedItem = items[randomIndex];

	selectedItem.posX = ofRandom(ofGetWidth());
	selectedItem.posY = ofRandom(ofGetHeight());

	ItemSpawn newItem;
	newItem.itemsEntities = selectedItem;
	newItem.spawnTime = ofGetElapsedTimef() + ofRandom(3, 10);

	activeItems.push_back(newItem);
}

//void ofApp::PrevItem()
//{
//	//si estamos en el inicio de la lista, ir al final
//
//	if (inventoryIterator == inventory.begin())
//	{
//		puts("inicio, moviendo al final");
//		inventoryIterator = inventory.end();
//		--inventoryIterator;
//	}
//	else
//	{
//		--inventoryIterator;
//		if (inventoryIterator == inventory.begin())
//		{
//			puts("llegando al inicio");
//		}
//	}
//
//	//inventoryIterator = inventory.begin();
//	std::cout << "item: " << (*inventoryIterator).name << "\n";
//}
//void ofApp::NextItem()
//{
//	++inventoryIterator;
//	if (inventoryIterator == inventory.end())
//	{
//		inventoryIterator = inventory.begin();
//	}
//
//	std::cout << "item: " << (*inventoryIterator).name << "\n";
//}
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
			weaponIndex++;
		}
		if (key == 57359)
		{
			std::cout << "item que sigue" << key << "\n";
			weaponIndex--;
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
