#pragma once
#include "Item.h"


class Heart: public Item
{
public:
	Heart(void);
	~Heart(void);
	void Effect(HUD &hd,int &i);
private:
	static const int health = 1;
};

