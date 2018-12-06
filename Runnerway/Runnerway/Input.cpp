#include <GL/freeglut.h>
#include <iostream>
#include "Math.h"
#include "MyHeader.h"

extern Ball ball;
extern Camera camera;
extern bool isJump;

inline void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':		// test
		printf("%d\n", camera.GetLorB());

		if (camera.GetLorB())
			camera.SetLorB(false);
		else
			camera.SetLorB(true);
		break;

	case VK_ESCAPE: case 'Q': case 'q':
		::PostQuitMessage(0);
		break;

	default:
		break;
	}
}

inline void SpecialKeyboard(int key, int x, int y)
{
	int mod = glutGetModifiers();

	if (mod == GLUT_ACTIVE_CTRL)
	{
		isJump = true;
	}

	if (camera.GetLorB())
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
}