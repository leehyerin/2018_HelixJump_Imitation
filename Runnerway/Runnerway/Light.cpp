#include "stdafx.h"

Light::Light()
{
	for (int i = 0; i < 4; ++i)
		AmbientLight[i] = 5.0f;
	
	DiffuseLightSnowman[0] = 1.0f;
	DiffuseLightSnowman[1] = 1.0f;
	DiffuseLightSnowman[2] = 0.0f;
	DiffuseLightSnowman[3] = 1.0f;

	for (int i = 0; i < 4; ++i)
		SpecularLightSnowman[i] = 1.0f;

	lightPosSnowman[0] = 0.0f;
	lightPosSnowman[1] = 10.0f;
	lightPosSnowman[2] = 0.0f;
	lightPosSnowman[3] = 1.0f;

	for (int i = 0; i < 3; ++i)
		gray[i] = 1.0f;
	gray[3] = 1.0f;
}

void Light::TurnOnAmbientLight()
{
	// Àü¿ª ÁÖº¯±¤
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
}