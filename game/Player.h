//Player.h
//zawiera pola i metody gracza

#pragma once
#include "Character.h"
#include <SFML\Graphics.hpp>

using namespace sf;

class Player: public Character
{
public:
	Player(void);					//zawiera wczytanie tekstur
	~Player(void);

	void GoRight();					//ruch w prawo
	void GoLeft();					//ruch w lewo
	void GoUp();					//ruch w górê
	void GoDown();					//ruch w dó³
	void PushDown(int x);			//przesuniêcie w dó³ o x
	void PushUp(int x);				//przesuniêcie w górê o x
	void Back();					//cofniêcie w zale¿noœci od kierunku ruchu
	void Stop();					//zaprzestanie ruchu
	void update();					//aktualizacja animacji

	int jumpflag;					//czy w trakcie skoku
	int jumpspeed;					//prêdkoœæ przy skoku
	int health;						//iloœæ zdrowia

private:
	Texture textable[22];			//tablica tekstur animacji gracza
};

