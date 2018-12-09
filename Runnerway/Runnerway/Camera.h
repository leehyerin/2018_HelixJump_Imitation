#pragma once

class Camera {
private:
	bool LorB;			// true Á¾ false È¾

public:
	Camera();
	~Camera() {}

	bool GetLorB() { return LorB; }

	void SetLorB(bool b) { LorB = b; }

	void CameraPos();

	void TitleCamera();
};