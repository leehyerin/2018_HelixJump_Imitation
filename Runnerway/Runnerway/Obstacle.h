#pragma once
#include "CCube.h"

class Obstacle :	public CCube
{
	int type;
public:
	Obstacle();
	Obstacle(float x, float y, float z, double r) : CCube(x, y, z, r) { type = rand() % 4 + 7; }
	~Obstacle();

	virtual void Draw();
	int GetType() { return type; };
};

