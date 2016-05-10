#include "Diamond.h"
#include <string>
#include "windows.h"

using namespace std;

Diamond::Diamond(void)
{
	try
	{
		if(!texture.loadFromFile("data/images/diamond.png")) throw string("data/images/diamond.png");
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

Diamond::~Diamond(void)
{
}

void Diamond::Effect(HUD &hd,int &i)
{
	status = INACTIVE;
	hd.score += score;
}