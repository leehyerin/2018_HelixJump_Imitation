#include <GL/freeglut.h>
#include "Math.h"
#include "Ground.h"


Ground::Ground()
{
	double angle = 0;
	double Floordegree = 0;
	double radius = 20;

	double x{ 0 }, z{ 0 };
	
	for (z = 0.0; z > -20.0; z -= 0.25)
	{
		Floordegree += 1;

		vMap.push_back(Map{ MyVec{x, 0.0, z }, Floordegree });
	}
	
	for (z = -20.0; z > -40.0; z -= 0.25)
	{
		Floordegree -= 1;

		vMap.push_back(Map{ MyVec{ x, 0.0, z }, Floordegree });
	}
}

Ground::~Ground()
{
}

void Ground::Draw()
{
	glPushMatrix();
	RED;
	
	for (unsigned int d = 0; d < vMap.size(); ++d)
			DrawQuads(vMap[d].m_pos.x, vMap[d].m_pos.z, vMap[d].m_degree);
}
void Ground::DrawQuads(double x, double z, double degree)
{
	glPushMatrix();
	{
		glTranslated(x, 0, z);
		glRotated(degree, 0, 1, 0);

		glBegin(GL_QUADS);
		{
			glVertex3d(x - 10.0, 0, z + 0.5);
			glVertex3d(x - 10.0, 0, z - 0.5);
			glVertex3d(x + 10.0, 0, z - 0.5);
			glVertex3d(x + 10.0, 0, z + 0.5);
		}
		glEnd();
	}
	glPopMatrix();
}
