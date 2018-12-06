#pragma once

class Item : public CCube
{
private:
	bool type;
public:
	Item() {}
	Item(float x, float y, float z, double r) : CCube(x, y, z, r) {};
	~Item() {}

	virtual void Draw();
};