#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

bool Enemy::Move()
{
	FloatRect enemy = GetGlobalBounds();
	if(status == DEAD && enemy.top < 721) sprite.move(0,3*speed);
	else if(status == GO_RIGHT && (enemy.left + enemy.width)< startx + movement) GoRight();
	else if(status == GO_RIGHT && (enemy.left + enemy.width)>= startx + movement) GoLeft();
	else if(status == GO_LEFT && enemy.left > startx) GoLeft();
	else if(status == GO_LEFT && enemy.left <= startx) GoRight();
	else return false;
	return true;
}

void Enemy::GoRight()
{
	status = GO_RIGHT;
	i++;
	if(i > 1) i = 0;
	sprite.move(speed,0);
}

void Enemy::GoLeft()
{
	status = GO_LEFT;
	i++;
	if(i < 2|| i > 3) i = 2;
	sprite.move(-speed,0);
}

void Enemy::update()
{
	sprite.setTexture(textable[i]);
}

bool Enemy::Contact(Player &player)
{
	FloatRect playr = player.GetGlobalBounds();
	FloatRect enmy = GetGlobalBounds();

	if(enmy.intersects(playr)) return true;
	return false;
}

void Enemy::OnContact(Player &player)
{
	FloatRect playr = player.GetGlobalBounds();
	FloatRect enmy = GetGlobalBounds();

	if((playr.top + playr.height)<=enmy.top+5)
	{
		if(status == GO_RIGHT) i = 4;
		else i = 5;
		status = DEAD;
	}
	else
	{ 
		player.health -= damage;
		player.Back();
	}
}