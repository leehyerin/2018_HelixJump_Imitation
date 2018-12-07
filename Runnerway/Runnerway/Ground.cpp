#include "stdafx.h"
#define CURVATURE 0.3f //°î·ü

Ground::Ground()
{
	float angle = 0;
	float Floordegree = 0;
	float radius = 20;

	float x{ 0 }, z{ 0 };

	for (z = 0.0; z > -40.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -40.0; z > -80.0; z -= 0.25)
	{
		Floordegree += CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -80.0; z > -120.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -120.0; z > -160.0; z -= 0.25)
	{
		Floordegree += CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -160.0; z > -200.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -200.0; z > -240.0; z -= 0.25)
	{
		Floordegree += CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}
}

Ground::~Ground()
{
}

void Ground::Draw()
{
	SOIL;
	for (unsigned int d = 0; d < vMap.size(); ++d)
		DrawQuads(vMap[d].m_pos.x, vMap[d].m_pos.z, vMap[d].m_degree);
	
}

void Ground::DrawQuads(float x, float z, float degree)
{
	glPushMatrix();
	{
		glTranslatef(x , 0, z - 0.5f);
		glRotatef(degree, 0, 1, 0);

		glBegin(GL_QUADS);
		{
			glVertex3f(+40, 0, 0);
			glVertex3f(+40, 0, 1.f);
			glVertex3f(-40.0f, 0, 1.f);
			glVertex3f(-40.0f, 0, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

float Ground::YDegreeOnTile(float x, float fz)
{
	int i;
	float z = -fz;

	int t = floor(z);
	double mod = z - t;

	if (mod < 0.25f) i = 0;
	else if(mod < 0.5f) i = 1;
	else if(mod < 0.75f) i = 2;
	else i = 3;

	float Z = -(t + i * 0.25f);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			return d.m_degree; break;
		}
	}
	return 0.0f;
}