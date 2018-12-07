#pragma once

class Ball {
private:
	float x, y, z;
	float radius;
	float rotX, rotY, rotZ;
	float speed;
	
	bool isJump;
	int time;

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
	float GetSpeed() { return speed; }
	bool GetIsJump() { return isJump; }
	int GetTime() { return time; }

	void SetPosX(float posx) { x = posx; }
	void SetPosY(float posy) { y = posy; }
	void SetPosZ(float posz) { z = posz; }
	void SetRotX(float x) { rotX = x; }
	void SetRotY(float y) { rotY = y; }
	void SetRotZ(float z) { rotZ = z; }
	void SetSpeed(float s) { speed = s; }
	void SetIsJump(bool b) { isJump = b; }
	void SetTime(int t) { time = t; }
};
