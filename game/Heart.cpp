#include "Heart.h"
#include <string>
#include "windows.h"

using namespace std;

Heart::Heart(void)
{
	try
	{
		if(!texture.loadFromFile("data/images/heart.png")) throw string("data/images/heart.png");
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

Heart::~Heart(void)
{
}

void Heart::Effect(HUD &hd,int &i)
{
	status = INACTIVE;
	hd.player.health += health;
}
