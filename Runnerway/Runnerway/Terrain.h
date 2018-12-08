#pragma once
#include "stdafx.h"

struct Map
{
	MyVec m_pos;
	float m_degree;
};

class Terrain
{
	vector<Map> vMap;
public:
	Terrain();
	~Terrain();

	void Draw(bool);
	void DrawHorizonQuads(float, float, float, float);
	void DrawVerticalQuads(float, float, float);

	float GetYDegreeOnTile(float, float);
	float GetHeightOnTile(float x, float z);
	float GetXNearTile(float x, float z);
	float GetZNearTile(float z);
};