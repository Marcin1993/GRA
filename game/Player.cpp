#include "Player.h"
#include "windows.h"
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;

Player::Player(void)
{
	try //sprawdzenie istenienia tekstur
	{
		string tmp;

		for(int i = 0; i <= 21; i++)
		{	
			if(i<9) tmp = "data/images/p1_walk0"+to_string(i+1)+".png";
			else if(i==9||i==10) tmp = "data/images/p1_walk"+to_string(i+1)+".png";
			else tmp = "data/images/p2_walk"+to_string(i+1)+".png";

			if(!textable[i].loadFromFile(tmp))
			{
				throw string(tmp);
				break;
			}
		}
	}
	catch(string ex)
	{
		string tmp = "Texture not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}

	sprite.setTexture(textable[0]);
	speed = 8;
	i = 0;
	status = GO_RIGHT;
	jumpflag = 0;
	jumpspeed = 28;
	health = 5;
}
Player::~Player(void)
{
}

void Player::GoLeft()
{
	status = GO_LEFT;
	i++;
	if(i < 11 || i > 21) i = 11; //reset iteratora animacji
	sprite.move(-speed, 0);
}
void Player::GoRight()
{
	status = GO_RIGHT;
	i++;
	if(i > 10) i = 0; //reset iteratora animacji
	sprite.move(speed, 0);
}
void Player::GoUp()
{
	if(status == GO_RIGHT)
	{
		i = 2; //iterator dla tekstury skoku w prawo
	}
	if(status == GO_LEFT)
	{
		i = 13; // iterator dla tekstury skoku w lewo
	}
	jumpflag = 1; //ustawienie flagi skoku
}
void Player::GoDown()
{
	if(status == GO_RIGHT)
	{
		i = 2; //iterator dla tekstury spadania w prawo
	}
	if(status == GO_LEFT)
	{
		i = 13; //iterator dla tekstury spadania w lewo
	}
	sprite.move(0, speed);
}
void Player::PushDown(int x)
{
	sprite.move(0,x);
}
void Player::PushUp(int x)
{
	sprite.move(0,-x);
}
void Player::Back()
{
	if(status==GO_RIGHT) sprite.move(-70,0);
	else if(status == GO_LEFT) sprite.move(70,0);
}
void Player::Stop()
{
	if(status == GO_RIGHT)
	{
		i = 0;	//iterator dla pierwszej tekstury ruchu w prawo
	}
	else if(status == GO_LEFT)
	{
		i = 11;	//iterator dla pierwszej tekstury ruchu w lewo
	}
}
void Player::update()
{
	sprite.setTexture(textable[i]);
}