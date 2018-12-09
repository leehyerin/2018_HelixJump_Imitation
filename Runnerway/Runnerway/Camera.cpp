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
		ball.SetStandard(0.0f);
		LorB = true;
	}
	//---------------------횡 구간-------------------------
	if (ball.GetPosZ() < -160.0f && ball.GetPosZ() > -320.0f)
	{
		ball.SetPosX(0.f);
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
		ball.SetStandard(-150.0f);
		LorB = true;
	}
	//---------------------횡 구간-------------------------
	if (ball.GetPosZ() < -680.0f && ball.GetPosZ() > -780.0f)
	{
		ball.SetPosX(-150.0f);
		LorB = false;
	}
	//---------------------종 구간-------------------------
	if (ball.GetPosZ() < -780.0f && ball.GetPosZ() > -1000.0f)
	{
		LorB = true;
	}

	if (LorB)
	{
		glTranslated(0.0f, 0.0f, -30.0f);

		glRotated(30.0f, 1.0f, 0.0f, 0.0f);
		glRotated(-terrain.GetYDegreeOnTile(ball.GetPosX(), ball.GetPosZ()), 0.0f, 1.0f, 0.0f);
		glRotated(0.0f, 0.0f, 0.0f, 1.0f);

		gluLookAt(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), 0.0f, 0.0f, ball.GetPosZ() - 500.0f, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glTranslated(0.0f, 0.0f, ball.GetPosX() - 30.0f);

		glRotated(0.0f, 1.0f, 0.0f, 0.0f);
		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
		glRotated(0.0f, 0.0f, 0.0f, 1.0f);

		gluLookAt(0.0f, ball.GetPosY(), ball.GetPosZ(), 0.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f);
	}
	//glPopMatrix();
}

void Camera::TitleCamera()
{
	glTranslated(0.0f, -5.0f, -15.0f);
	glRotated(10.0f, 1.0f, 0.0f, 0.0f);
}

void Camera::ResultCamera()
{
	glTranslated(0.0f, -15.0f, -15.0f);
	glRotated(10.0f, 1.0f, 0.0f, 0.0f);
}