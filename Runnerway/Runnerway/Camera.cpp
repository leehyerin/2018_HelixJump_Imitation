#include <gl/freeglut.h>
#include "Camera.h"
#include "Ball.h"
#include <stdio.h>

extern Ball ball;

Camera::Camera()
{
	LorB = true;
}

void Camera::CameraPos()
{
	if (LorB)
	{
		glTranslated(0.0f, 0.0f, -30.0f);

		glRotated(30.0f, 1.0f, 0.0f, 0.0f);
		glRotated(0.0f, 0.0f, 1.0f, 0.0f);
		glRotated(0.0f, 0.0f, 0.0f, 1.0f);

		gluLookAt(0.0f, 0.0f, ball.GetPosZ(), 0.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		glTranslated(0.0f, 0.0f, -50.0f);

		glRotated(0.0f, 1.0f, 0.0f, 0.0f);
		glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
		glRotated(0.0f, 0.0f, 0.0f, 1.0f);

		gluLookAt(0.0f, 0.0f, ball.GetPosZ(), 0.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f);
	}
}