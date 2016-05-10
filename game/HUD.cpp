#include "HUD.h"
#include <string>
#include "windows.h"

using namespace std;

HUD::HUD(Player &playr):player(playr)
{
	try
	{
		if(!texture.loadFromFile("data/images/heart.png"))
			throw string("data/images/heart.png");
		if(!font.loadFromFile("data/fonts/menu.ttf"))
			throw string("data/fonts/menu.ttf");
	}
	catch(string ex)
	{
		string tmp = "File not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}
	sprite.setTexture(texture);
	sprite.setPosition(0,0);
	text.setFont(font);
	text.setCharacterSize(40);
	score = 0;
	changeflag = 1;
}

HUD::~HUD(void)
{
}

void HUD::Draw(RenderWindow &window)
{
	int i = player.health;
	string txt;

	text.setString("Score: "+to_string(score));
	text.setPosition(1280 - text.getGlobalBounds().width - 10,10);

	for(i = 0; i < player.health; i++)
	{
		window.draw(sprite);
		sprite.move(30,0);
	}
	sprite.setPosition(0,0);

	window.draw(text);
}
