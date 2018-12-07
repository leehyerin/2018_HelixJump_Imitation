#pragma once

enum ITEMTYPE
{
	DASH,
	BOMB, //반경 (x cm) 다 터뜨리는 거
	ANSWER
};

class Item : public CCube
{
private:	
	ITEMTYPE m_Type;
	MyVec m_Color{ 0,0,0 };
public:
	Item() {}
	Item(float x, float y, float z, double r) : CCube(x, y, z, r) {};
	~Item() {}

	void SetColor(float, float, float);
	virtual void Draw();
};