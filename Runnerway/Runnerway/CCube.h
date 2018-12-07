#pragma once
#include "MyVec.h"

class CCube
{
private:
	MyVec m_Pos;
	double m_Radius{ 10.0 };
public:
	CCube();
	CCube(float, float,float, double);
	~CCube();

	bool CheckCollPlayerbyItem(float x, float y, float z, float radius);

	virtual void Draw();
};

