#pragma once
#include "MyVec.h"
#include <iostream>

class Particle
{
private:
	MyVec m_Pos;
	MyVec m_Dir;

public:
	Particle(double x, double y, double z);

	inline void Update() { m_Pos = m_Pos + m_Dir; }
	inline MyVec* GetPos() { return &m_Pos; }
};
