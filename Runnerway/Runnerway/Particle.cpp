#include "stdafx.h"

Particle::Particle(double x, double y, double z)
{
	m_Pos.x = x + rand() % 6 - 3;
	m_Pos.y = y + rand() % 6 - 3;
	m_Pos.z = z + rand() % 6 - 3;

	m_Dir.x = rand() % 2;
	m_Dir.y = rand() % 2;
	m_Dir.z = rand() % 2;
	 
	//---------------Normalization---------------
	double len = sqrt(m_Dir.x*m_Dir.x + m_Dir.y*m_Dir.y + m_Dir.z*m_Dir.z);
	m_Dir.x /= len;
	m_Dir.y /= len;
	m_Dir.z /= len;
}

Particle::Particle(double x, double y, double z, int t)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
	time = t;
}

void Particle::SetPos(double x, double y, double z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}