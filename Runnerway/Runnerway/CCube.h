#pragma once
#include "MyVec.h"
#include "Particle.h"

class CCube
{
private:
	MyVec m_Pos;
	double m_Radius{ 10.0 };

public:
	CCube();
	CCube(float, float, float, double);
	~CCube();

	MyVec* GetPos() { return &m_Pos; }

	bool CheckCollPlayerbyItem(float x, float y, float z, float radius);

	virtual void Draw();
};

