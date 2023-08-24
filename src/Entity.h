#pragma once
#include <string>
#include <random>
#include "ofMain.h"
//#include "GenericArray.h"

class Entity
{
public:
	std::string name;
	int health;

	Entity();

	const char* toString();

	ofVec2f* position;
	ofVec2f* Velocity;

	void draw();

	float posX, posY;
};

//template<>
//inline void GenericArray<Entity>::listContents()
//{
//	for (int i = 0; i < size; i++)
//	{
//		std::cout << "[" << i << "] = " << array[i].toString() << std::endl;
//	}
//}

