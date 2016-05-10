#pragma once
#include "Player.h"
#include "HUD.h"
#include <SFML\Graphics.hpp>

using namespace sf;

class Item: public Drawable, Transformable
{
public:
	Item(void);
	~Item(void);

	enum ItemState
	{
		ACTIVE,
		INACTIVE,
	};

	ItemState status;

	bool Contact(Player &player);
	void PlaceItem(int x, int y);
	virtual void Effect(HUD &hd, int &i)=0;
	void draw(RenderTarget &target, RenderStates states) const;
protected:
	Sprite sprite;
	Texture texture;
};

