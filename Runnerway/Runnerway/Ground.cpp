#include "stdafx.h"

Ground::Ground()
{
	float angle = 0;
	float Floordegree = 0;
	float radius = 20;

	float x{ 0 }, z{ 0 };

	for (z = 0.0; z > -40.0; z -= 0.25)
	{
		Floordegree += 0.1;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -40.0; z > -80.0; z -= 0.25)
	{
		Floordegree -= 0.1;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -80.0; z > -120.0; z -= 0.25)
	{
		Floordegree += 0.1;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}
}

Ground::~Ground()
{
}

void Ground::Draw()
{
	glPushMatrix();
	SOIL;
	for (unsigned int d = 0; d < vMap.size(); ++d)
		DrawQuads(vMap[d].m_pos.x, vMap[d].m_pos.z, vMap[d].m_degree);
}

void Ground::DrawQuads(float x, float z, float degree)
{
	glPushMatrix();
	{
		glTranslatef(x, 0, z);
		glRotatef(degree, 0, 1, 0);

		glBegin(GL_QUADS);
		{
			glVertex3f(x - 20.0, 0, z + 0.5);
			glVertex3f(x - 20.0, 0, z - 0.5);
			glVertex3f(x + 20.0, 0, z - 0.5);
			glVertex3f(x + 20.0, 0, z + 0.5);
		}
		glEnd();
	}
	glPopMatrix();
}

float Ground::YDegreeOnTile(float x, float z)
{
	auto X = floor(x);
	auto Z = floor(z);

	for (auto d : vMap)
		if (d.m_pos.z == Z)
		{
			cout << d.m_degree << endl;
			return d.m_degree; break;
		}
	return 0.0f;
}