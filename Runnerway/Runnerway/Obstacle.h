#pragma once
#include "CCube.h"

class Obstacle :	public CCube
{
public:
	Obstacle();
	Obstacle(float x, float y, float z, double r) : CCube(x, y, z, r) {};
	~Obstacle();

	virtual void Draw();
};

