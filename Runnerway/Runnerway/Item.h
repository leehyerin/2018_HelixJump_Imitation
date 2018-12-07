#pragma once

enum ITEMTYPE
{
	DASH,
	BOMB,
	ANSWER
};

class Item : public CCube
{
private:
	ITEMTYPE m_Type;
	MyVec m_Color{ 0,0,0 };

public:
	Item() {}
	Item(float x, float y, float z, double r, int type) : CCube(x, y, z, r) { m_Type = (ITEMTYPE)type; };
	~Item() {}

	virtual void Draw();
	void SetColor(float R, float G, float B) { m_Color.x = R, m_Color.y = G, m_Color.z = B; }
};