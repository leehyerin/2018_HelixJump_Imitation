#pragma once
#include <gl/freeglut.h>

class Light
{
private:
	GLfloat AmbientLight[4];

	GLfloat DiffuseLightSnowman[4];
	GLfloat SpecularLightSnowman[4];
	GLfloat lightPosSnowman[4];
	GLfloat gray[4];

public:
	Light();
	~Light() {}

	void TurnOnAmbientLight();
};