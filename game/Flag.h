#pragma once
#include "Item.h"

class Flag : public Item
{
public:
	Flag(void);
	~Flag(void);
	void Effect(HUD &hd,int &i);
};

