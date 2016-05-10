#include "Flag.h"
#include "Level.h"
#include "windows.h"
#include <string>
using namespace std;

Flag::Flag(void)
{
	try
	{
		if(!texture.loadFromFile("data/images/flag.png")) throw string("data/images/flag.png");
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

Flag::~Flag(void)
{
}

void Flag::Effect(HUD &hd,int &i)
{
	hd.changeflag = 1;
	++i;
}