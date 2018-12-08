#include "stdafx.h"
#define CURVATURE 0.15f //곡률

extern Camera camera;

Terrain::Terrain()
{
	float angle = 0;
	float Floordegree = 0;
	float radius = 20;

	float x{ 0 }, y{ 0 }, z{ 0 };
	
	//---------------------종 구간-------------------------
	for (z = 0.0; z > -80.0; z -= 0.25)
	{
		camera.SetLorB(true);

		Floordegree += CURVATURE;
		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -80.0; z > -160.0; z -= 0.25)
	{
		camera.SetLorB(true);

		Floordegree -= CURVATURE;
		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------횡 구간-------------------------
	Floordegree = 0;
	for (z = -160.0; z > -240.0; z -= 0.25)
	{
		camera.SetLorB(false);

		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -240.0; z > -320.0; z -= 0.25)
	{
		camera.SetLorB(false);

		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------종 구간-------------------------
	for (z = -320.0; z > -400.0; z -= 0.25)
	{
		camera.SetLorB(true);

		Floordegree += CURVATURE;
		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -400.0; z > -450.0; z -= 0.25)
	{
		camera.SetLorB(true);

		Floordegree -= CURVATURE;
		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------갈림길-------------------------
	///왼쪽--맞는 길
	x = 0.f; Floordegree = 30; 
	for (z = -450.0; z > -600.0; z -= 0.25)
	{
		Floordegree -= 0.1f;
		x -= 0.25f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	float tx = x;
	float tFloordegree = Floordegree;

	///오른쪽
	x = 0.f; Floordegree = -30;
	for (z = -450.0; z > -600.0; z -= 0.25)
	{
		Floordegree += 0.1f;
		x += 0.25f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------종 구간-------------------------
	x = tx;		
	Floordegree = tFloordegree;

	for (z = -600.0; z > -680.0; z -= 0.25)
	{
		camera.SetLorB(true);

		Floordegree += CURVATURE;
		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------횡 구간-------------------------
	for (z = -680.0; z > -780.0; z -= 0.25)
	{
		camera.SetLorB(false);

		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------종 구간-------------------------
	for (z = -780.0; z > -900.0; z -= 0.25)
	{
		camera.SetLorB(true);

		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -900.0; z > -1000.0; z -= 0.25)
	{
		camera.SetLorB(true);

		Floordegree += CURVATURE;
		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
}

Terrain::~Terrain()
{
}

void Terrain::Draw(bool b) //true 종 
{
	SOIL;
	if (b)
	{
		for (auto d : vMap)
			DrawHorizonQuads(d.m_pos.x, d.m_pos.y, d.m_pos.z, d.m_degree);
	}
	else 
	{
		for (auto d : vMap)
			DrawVerticalQuads(d.m_pos.x, d.m_pos.y, d.m_pos.z);
	}
}

void Terrain::DrawHorizonQuads(float x, float y, float z, float degree)
{
	glPushMatrix();
	{
		glTranslatef(x , y, z - 0.5f);
		glRotatef(degree, 0, 1, 0);	
		glRotatef(y, 1, 0, 0);

		glBegin(GL_QUADS);
		{
			glVertex3f(+30.f, 0, 0.f);
			glVertex3f(+30.f, 0, 1.f);
			glVertex3f(-30.f, 0, 1.f);
			glVertex3f(-30.f, 0, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

void Terrain::DrawVerticalQuads(float x, float y, float z)
{
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		{
			glVertex3f(x, y, z);
			glVertex3f(x, y, z + 1.f);
			glVertex3f(x, -30.f, z + 1.f);
			glVertex3f(x, -30.f, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

float Terrain::GetYDegreeOnTile(float x, float fz)
{
	float Z = GetZNearTile(-fz);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			//cout << d.m_degree << "\n";
			return d.m_degree; break;
		}
	}
	return 0.0f;
}

float Terrain::GetHeightOnTile(float x,float fz)
{
	float Z = GetZNearTile(-fz);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			return d.m_pos.y; break;
		}
	}
	return 0.0f;
}

float Terrain::GetXNearTile(float ballX, float ballZ)
{
	float BALLZ = ballZ;

	float Z = GetZNearTile(-BALLZ);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			if (ballX <= 0)				//x가 음수일 때는 왼쪽 길, 양수일 때는 오른쪽 길
			{
				cout << "왼쪽 타일 정보는=" << d.m_pos.x << "\t" << Z << "\n";

				return  d.m_pos.x;
			}
			else
			{
				cout << ballX << "오른쪽 타일 정보는=" << d.m_pos.x << "\t" << Z << "\n";

				return  -d.m_pos.x;
			}
		}
	}
}

float Terrain::GetZNearTile(float z)
{
	float Z;

	int i = 0;
	int t = floor(z);
	double mod = z - t;

	if (mod < 0.25f) i = 0;
	else if (mod < 0.5f) i = 1;
	else if (mod < 0.75f) i = 2;
	else i = 3;

	Z =  -(t + i * 0.25f);
	return Z;
}
