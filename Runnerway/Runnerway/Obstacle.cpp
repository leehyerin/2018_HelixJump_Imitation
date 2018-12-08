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
	CCube::Draw(2, 2.0f);
}
