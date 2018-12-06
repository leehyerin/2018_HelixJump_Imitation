#include <GL/freeglut.h>
#include <iostream>
#include "Ball.h"
#include "Math.h"

extern Ball cBall;
extern double dx,dy,z;


inline void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: case 'Q': case 'q':
		::PostQuitMessage(0);
		break;
	case 'z': z -= 1; break;
	case 'Z': z += 1; break;
	case 'x': dx -= 1; break;
	case 'X': dx += 1; break;
	case 'y': dy -= 1; break;
	case 'Y': dy += 1; break;

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
		cBall.SetRotX(cBall.GetRotX() - 3);
		cBall.SetPosX(cBall.GetRotX() - 1 * PI * cBall.GetRadius() / 360);
	}
		break;

	case GLUT_KEY_RIGHT:
	{
		cBall.SetRotX(cBall.GetRotX() + 3);
		cBall.SetPosX(cBall.GetRotX() + 1 * PI * cBall.GetRadius() / 360);
	}
		break;

	default:
		break;
	}
}