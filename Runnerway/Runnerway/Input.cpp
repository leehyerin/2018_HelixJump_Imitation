#include <GL/freeglut.h>
#include <iostream>
#include "Ball.h"
#include "Math.h"

extern Ball ball;

inline void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: case 'Q': case 'q':
		::PostQuitMessage(0);
		break;

	default:
		break;
	}
}

inline void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		ball.SetRotX(ball.GetRotX() - 3);
		ball.SetPosX(ball.GetRotX() - 1 * PI * ball.GetRadius() / 360);
	}
		break;

	case GLUT_KEY_RIGHT:
	{
		ball.SetRotX(ball.GetRotX() + 3);
		ball.SetPosX(ball.GetRotX() + 1 * PI * ball.GetRadius() / 360);
	}
		break;

	default:
		break;
	}
}