#include "EnemySnail.h"
#include <string>
#include "windows.h"

using namespace std;

EnemySnail::EnemySnail(void)
{
	try
	{
		if(!textable[0].loadFromFile("data/images/snailright1.png"))
			throw string("data/images/snailright1.png");
		if(!textable[1].loadFromFile("data/images/snailright2.png"))
			throw string("data/images/snailright2.png");
		if(!textable[2].loadFromFile("data/images/snailleft1.png"))
			throw string("data/images/snailleft1.png");
		if(!textable[3].loadFromFile("data/images/snailleft2.png"))
			throw string("data/images/snailleft2.png");
		if(!textable[4].loadFromFile("data/images/snaildead1.png"))
			throw string("data/images/snaildead1.png");
		if(!textable[5].loadFromFile("data/images/snaildead2.png"))
			throw string("data/images/snaildead2.png");
	}
	catch(string ex)
	{
		string tmp = "Texture not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}

	sprite.setTexture(textable[0]);
	status = GO_RIGHT;
	damage = 1;
	speed = 1;
	movement = 200;
	i = 0;
}

EnemySnail::~EnemySnail(void)
{
}
