#include "stdafx.h"

extern Ball ball;
extern Camera camera;
extern int scenenum;

inline void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	//case 'p':		// test
	//	if (camera.GetLorB())
	//		camera.SetLorB(false);
	//	else
	//		camera.SetLorB(true);
	//	break;

	case 13:
		if (scenenum == 0)
			scenenum = 1;
		else if (scenenum == 2)
		{
			scenenum = 0;
			ball.SetTexTime(0);
		}
		break;

	case VK_ESCAPE:
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
		if (false == ball.GetActive())
			ball.SetIsJump(true);
	}

	if (camera.GetLorB())
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
		{
			if (ball.GetPosX() > ball.GetStandard() - 20.0f)
			{
				ball.SetRotX(ball.GetRotX() - 5);
				ball.SetPosX(ball.GetStandard() + ball.GetRotX() - 1 * PI * ball.GetRadius() / 360);
			}
		}
		break;

		case GLUT_KEY_RIGHT:
		{
			if (ball.GetPosX() < ball.GetStandard() + 20.0f)
			{
				ball.SetRotX(ball.GetRotX() + 5);
				ball.SetPosX(ball.GetStandard() + ball.GetRotX() + 1 * PI * ball.GetRadius() / 360);
			}
		}
		break;

		default:
			break;
		}
	}
}