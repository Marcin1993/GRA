#include "EnemyFly.h"
#include "windows.h"
#include <string>

using namespace std;

EnemyFly::EnemyFly(void)
{
	try
	{
		if(!textable[0].loadFromFile("data/images/flyFly3.png"))
			throw string("data/images/flyFly3.png");
		if(!textable[1].loadFromFile("data/images/flyFly4.png"))
			throw string("data/images/flyFly4.png");
		if(!textable[2].loadFromFile("data/images/flyFly1.png"))
			throw string("data/images/flyFly1.png");
		if(!textable[3].loadFromFile("data/images/flyFly2.png"))
			throw string("data/images/flyFly2.png");
		if(!textable[4].loadFromFile("data/images/flyDead2.png"))
			throw string("data/images/flyDead2.png");
		if(!textable[5].loadFromFile("data/images/flyDead.png"))
			throw string("data/images/flyDead.png");
	}
	catch(string ex)
	{
		string tmp = "Texture not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}

	sprite.setTexture(textable[0]);
	status = GO_RIGHT;
	damage = 2;
	speed = 2;
	movement = 250;
	i = 0;
}

EnemyFly::~EnemyFly(void)
{
}
