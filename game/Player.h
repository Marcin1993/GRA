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
	void GoUp();					//ruch w g�r�
	void GoDown();					//ruch w d�
	void PushDown(int x);			//przesuni�cie w d� o x
	void PushUp(int x);				//przesuni�cie w g�r� o x
	void Back();					//cofni�cie w zale�no�ci od kierunku ruchu
	void Stop();					//zaprzestanie ruchu
	void update();					//aktualizacja animacji

	int jumpflag;					//czy w trakcie skoku
	int jumpspeed;					//pr�dko�� przy skoku
	int health;						//ilo�� zdrowia

private:
	Texture textable[22];			//tablica tekstur animacji gracza
};

