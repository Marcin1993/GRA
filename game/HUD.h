//HUD.h
//obs³uga informacji gry

#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
using namespace sf;

class HUD
{
public:
	HUD(Player &playr);
	~HUD(void);
	void Draw(RenderWindow &window);			//rysuje elementy HUD'a w oknie

	Player &player;
	int score;									//wynik punktowy gracza
	int changeflag;								//flaga zmiany poziomu

private:
	Font font;
	Text text;
	Sprite sprite;
	Texture texture;
};

