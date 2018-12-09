#include "stdafx.h"

extern Ball ball;

Light::Light()
{
	for (int i = 0; i < 4; ++i)
		AmbientLight[i] = 1.5f;
	
	DiffuseLightSnowman[0] = 1.0f;
	DiffuseLightSnowman[1] = 1.0f;
	DiffuseLightSnowman[2] = 1.0f;
	DiffuseLightSnowman[3] = 1.0f;

	for (int i = 0; i < 4; ++i)
		SpecularLightSnowman[i] = 0.5f;

	lightPosSnowman[0] = ball.GetPosX();
	lightPosSnowman[1] = ball.GetPosY();
	lightPosSnowman[2] = ball.GetPosZ();
	lightPosSnowman[3] = 1.0f;

	for (int i = 0; i < 3; ++i)
		gray[i] = 0.5f;
	gray[3] = 1.0f;
}

void Light::TurnOnAmbientLight()
{
	// 전역 주변광
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
}

void Light::TurnOnSnowmanLight()
{
	// 조명을 사용하도록 설정 
	glEnable(GL_LIGHTING);

	// 조명 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLightSnowman);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLightSnowman);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosSnowman);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLightSnowman);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_LIGHT0);
}