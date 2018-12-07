#pragma once
#include "MyVec.h"
#include <iostream>

class Particle
{
private:
	MyVec m_Pos;
	MyVec m_Dir;
	int time;

public:
	Particle(double x, double y, double z);
	Particle(double x, double y, double z, int t);

	inline void Update() { m_Pos = m_Pos + m_Dir; }
	inline MyVec* GetPos() { return &m_Pos; }
	void SetPos(double x, double y, double z);
	inline int GetTime() { return time; }
	inline void SetTime(int t) { time = t; }
};