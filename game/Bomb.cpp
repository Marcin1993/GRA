#include "Bomb.h"
#include <string>
#include "windows.h"

using namespace std;

Bomb::Bomb(void)
{
	try
	{
		if(!texture.loadFromFile("data/images/bomb.png")) throw string("data/images/bomb.png");
	}
	catch(string ex)
	{
		string tmp = "Texture not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}
	sprite.setTexture(texture);
	status = ACTIVE;
}

Bomb::~Bomb(void)
{
}

void Bomb::Effect(HUD &hd,int &i)
{
	hd.player.health -= damage;
	hd.player.Back();
}