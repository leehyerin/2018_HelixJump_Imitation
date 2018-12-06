#pragma once
#include "MyHeader.h"
#include "MyVec.h"

struct Map
{
	MyVec m_pos;
	double m_degree;

};

class Ground
{
	vector<Map> vMap;
public:
	Ground();
	~Ground();
	void Draw();
	void DrawQuads(double, double, double);
};

