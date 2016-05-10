#include "Character.h"

Character::Character(void)
{
}

Character::~Character(void)
{
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

Vector2f Character::GetPosition()
{
	return sprite.getPosition();
}

FloatRect Character::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

int Character::getSpeed()
{
	return speed;
} 

void Character::PlaceCharacter(int x, int y)
{
	sprite.setPosition(x, y);
}