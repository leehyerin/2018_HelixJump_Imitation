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

public:
	Item() {}
	Item(float x, float y, float z, double r, int type) : CCube(x, y, z, r) { m_Type = (ITEMTYPE)type; };
	~Item() {}

	int GetItemType() { return (int)m_Type; }
	
	virtual void Draw();
};