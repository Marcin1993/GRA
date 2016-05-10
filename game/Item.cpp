#include "Item.h"

Item::Item(void)
{
}

Item::~Item(void)
{
}

bool Item::Contact(Player &player)
{
	FloatRect playr = player.GetGlobalBounds();
	FloatRect itm = sprite.getGlobalBounds();

	if(status == ACTIVE && itm.intersects(playr)) return true;
	return false;
}

void Item::PlaceItem(int x, int y)
{
	sprite.setPosition(x,y);
}

void Item::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}
