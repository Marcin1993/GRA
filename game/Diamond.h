#pragma once
#include "Item.h"

class Diamond : public Item
{
public:
	Diamond(void);
	~Diamond(void);
	void Effect(HUD &hd,int &i);
private:
	static const int score = 100;
};

