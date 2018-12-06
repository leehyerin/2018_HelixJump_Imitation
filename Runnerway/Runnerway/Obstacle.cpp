#include "Obstacle.h"
#include <GL/freeglut.h>
#include "MyHeader.h"



Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{
	BLACK;
	CCube::Draw();
}
