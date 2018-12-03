#include <GL/freeglut.h>

inline void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: 	case 'Q':	case 'q':
		::PostQuitMessage(0);
		break;
	default:
		break;
	}
}