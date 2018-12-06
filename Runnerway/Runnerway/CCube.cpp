#include "CCube.h"
#include <GL/freeglut.h>

CCube::CCube()
{
}

CCube::CCube(float x, float y, float z, double r)
{
	m_Pos = { x,y,z };
	m_Radius = r;
}

CCube::~CCube()
{
}

void CCube::Draw()
{
	glPushMatrix();
	{
		glTranslated(m_Pos.x, m_Pos.y, m_Pos.z);
		glutSolidCube(m_Radius);
	}
	glPopMatrix();
}

bool CCube::CheckCollPlayerbyItem(float x, float y, float z, float radius)
{
	if (CheckCollRectbyLine(m_Pos.x, x, m_Radius, radius))
		if (CheckCollRectbyLine(m_Pos.y, y, m_Radius, radius))
			if (CheckCollRectbyLine(m_Pos.z, z, m_Radius, radius))  return true;

	return false;
}

