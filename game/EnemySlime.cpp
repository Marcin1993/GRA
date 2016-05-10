#include "EnemySlime.h"
#include <string>
#include "windows.h"

using namespace std;

EnemySlime::EnemySlime(void)
{
	try
	{
		if(!textable[0].loadFromFile("data/images/slimeWalk3.png"))
			throw string("data/images/slimeWalk3.png");
		if(!textable[1].loadFromFile("data/images/slimeWalk4.png"))
			throw string("data/images/slimeWalk4.png");
		if(!textable[2].loadFromFile("data/images/slimeWalk1.png"))
			throw string("data/images/slimeWalk1.png");
		if(!textable[3].loadFromFile("data/images/slimeWalk2.png"))
			throw string("data/images/slimeWalk2.png");
		if(!textable[4].loadFromFile("data/images/slimeDead2.png"))
			throw string("data/images/slimeDead2.png");
		if(!textable[5].loadFromFile("data/images/slimeDead.png"))
			throw string("data/images/slimeDead.png");
	}
	catch(string ex)
	{
		string tmp = "Texture not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}

	sprite.setTexture(textable[0]);
	status = GO_RIGHT;
	damage = 3;
	speed = 1;
	movement = 300;
	i = 0;
}

EnemySlime::~EnemySlime(void)
{
}
