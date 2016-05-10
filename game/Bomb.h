#pragma once
#include "Item.h"

class Bomb: public Item
{
public:
	Bomb(void);
	~Bomb(void);
	void Effect(HUD &hd, int &i);
private:
	static const int damage = 2;
};

