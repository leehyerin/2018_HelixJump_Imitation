#include "stdafx.h"

extern Ball ball;
extern Terrain terrain;

Camera::Camera()
{
	LorB = true;
}

void Camera::CameraPos()
{
	//---------------------종 구간-------------------------
	if (ball.GetPosZ() > -160.0f)
	{
		LorB = true;
	}
	//---------------------횡 구간-------------------------
	if (ball.GetPosZ() < -160.0f && ball.GetPosZ() > -320.0f)
	{
		LorB = false;
	}
	//---------------------종 구간-------------------------
	if (ball.GetPosZ() < -320.0f && ball.GetPosZ() > -450.0f)
	{
		LorB = true;
	}
	//---------------------갈림길-------------------------
	if (ball.GetPosZ() < -450.0f && ball.GetPosZ() > -600.0f)
	{
		LorB = false;
	}
	//---------------------종 구간-------------------------
	if (ball.GetPosZ() < -600.0f && ball.GetPosZ() > -680.0f)
	{
		LorB = true;
	}
	//---------------------횡 구간-------------------------
	if (ball.GetPosZ() < -680.0f && ball.GetPosZ() > -780.0f)
	{
		LorB = false;
	}
	//---------------------종 구간-------------------------
	if (ball.GetPosZ() < -780.0f && ball.GetPosZ() > -1000.0f)
	{
		LorB = true;
	}

	//glPushMatrix();
	if (LorB)
	{
		glTranslated(0.0f, 0.0f, -30.0f);

		glRotated(30.0f, 1.0f, 0.0f, 0.0f);
		glRotated(-terrain.GetYDegreeOnTile(ball.GetPosX(), ball.GetPosZ()), 0.0f, 1.0f, 0.0f);
		glRotated(0.0f, 0.0f, 0.0f, 1.0f);

		gluLookAt(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), 0.0f, 0.0f, -1000.0f, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glTranslated(0.0f, 0.0f, -30.0f);

		glRotated(0.0f, 1.0f, 0.0f, 0.0f);
		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
		glRotated(0.0f, 0.0f, 0.0f, 1.0f);

		gluLookAt(0.0f, 0.0f, ball.GetPosZ(), 0.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f);
	}
	//glPopMatrix();
}