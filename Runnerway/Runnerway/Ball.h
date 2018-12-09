#pragma once
#include "Particle.h"
#include <vector>
#include <iterator>
using namespace std;

class Ball {
private:
	float x, y, z;
	float radius;
	float rotX, rotY, rotZ;
	float speed;

	bool isJump;
	int JumpTime;
	int accelTime;
	float standard;

	bool isActive;

	int Particletype;
	int TexIdx{ 11 };
	int TexTimer{ 1 };
	//
	bool m_bParticle{ false };
	vector<Particle> m_vParticles;
	int m_Timer{ 0 };

	vector<Particle> runParticles;
	vector<Particle>::iterator particleIter;

public:
	Ball();
	~Ball();

	void Update();
	void DrawBall();

	float GetPosX() { return x; }
	float GetPosY() { return y; }
	float GetPosZ() { return z; }
	float GetRotX() { return rotX; }
	float GetRotY() { return rotY; }
	float GetRotZ() { return rotZ; }
	float GetRadius() { return radius; }
	float GetSpeed() { return speed; }
	bool GetIsJump() { return isJump; }
	int GetTime() { return JumpTime; }
	float GetStandard() { return standard; }
	bool GetActive() { return isActive; }

	void SetPosX(float posx) { x = posx; }
	void SetPosY(float posy) { y = posy; }
	void SetPosZ(float posz) { z = posz; }
	void SetRotX(float x) { rotX = x; }
	void SetRotY(float y) { rotY = y; }
	void SetRotZ(float z) { rotZ = z; }
	void SetSpeed(float s) { speed = s; }
	void SetIsJump(bool b) { isJump = b; }
	void SetTime(int t) { JumpTime = t; }
	void SetStandard(float s) { standard = s; }

	void CompareAddPosX(float prevX, float currX) { x = x + (currX - prevX); }
	//
	void ParticleStart(MyVec*, int);
	void ParticleProcess();
	void ParticleDraw();

	void RunParitcle();
	void RunParticleDraw();

	//
	void Accelartion(int);
};
