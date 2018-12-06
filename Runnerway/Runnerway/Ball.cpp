#include <GL/freeglut.h>
#include "MyHeader.h"
#include "Ball.h"

Ball::Ball()
{
	x = 0.0f, y = 0.0f, z = 0.0f;
	radius = 5.0f;
	rotZ = 0.0f;
	speed = 10.0f;
}

Ball::~Ball()
{
}

void Ball::DrawBall()
{
	glPushMatrix();
	{
		WHITE;
		glTranslatef(x, 0.0f, 0.0f);
		glTranslatef(0.0f, y, 0.0f);
		glTranslatef(0.0f, 0.0f, z);
		glRotatef(rotZ, 1.0f, 0.0f, 0.0f);
		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotX, 0.0f, 0.0f, 1.0f);
		glutSolidSphere(radius, 20, 10);
		BLACK;
		glutWireSphere(radius, 20, 10);
	}
	glPopMatrix();
}