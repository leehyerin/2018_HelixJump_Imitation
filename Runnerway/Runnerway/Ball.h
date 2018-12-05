#pragma once

class Ball {
private:
	float x, y, z;
	float radius;
	float rotX, rotY, rotZ;
	float test;

public:
	Ball();
	~Ball();

	void DrawBall();

	float GetPosX() { return x; }
	float GetPosY() { return y; }
	float GetPosZ() { return z; }
	float GetRotX() { return rotX; }
	float GetRotY() { return rotY; }
	float GetRotZ() { return rotZ; }
	float GetRadius() { return radius; }

	void SetPosX(float posx) { x = posx; }
	void SetPosY(float posy) { y = posy; }
	void SetPosZ(float posz) { z = posz; }
	void SetRotX(float x) { rotX = x; }
	void SetRotY(float y) { rotY = y; }
	void SetRotZ(float z) { rotZ = z; }
};
