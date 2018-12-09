#include "stdafx.h"

Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{
	WHITE;

	CCube::Draw(type, 2.0f);
}
