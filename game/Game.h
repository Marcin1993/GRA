//Game.h
//obsluga stanu gry
#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
 
using namespace std;
using namespace sf;

class Game
{
public:
	Game(void);
	~Game(void);
	void RunGame();		//uruchamia grê
protected:				//mo¿liwe stany gry
	enum GameState{
		MENU ,
		GAME ,
		LOAD ,
		END ,
	};

	GameState state;	//aktualny stan gry
private:
	int it;				//numer poziomu do wczytania
	Font font;			//czcionka menu
	void menum();		//obsluga glownego menu
	void single();		//obsluga singleplayer
	void load();		//obsluga wczytywania poziomu
};

