#pragma once
#include "stdafx.h"

struct Map
{
	MyVec m_pos;
	float m_degree;
};

class Ground
{
	vector<Map> vMap;
public:
	Ground();
	~Ground();
	void Draw(bool);
	void DrawHorizonQuads(float, float, float, float);
	void DrawVerticalQuads(float, float, float);
	float YDegreeOnTile(float, float);
	float GetHeightOnTile(float x, float z);
};