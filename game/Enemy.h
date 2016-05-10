#pragma once
#include "Character.h"
#include "Player.h"

class Enemy: public Character
{
public:
	Enemy(void);
	virtual ~Enemy(void);

	bool Move();						//wykonanie ruchu
	void GoRight();						//ruch w prawo
	void GoLeft();						//ruch w lewo
	void update();						//aktualizacja tekstury
	bool Contact(Player &player);		//czy nast¹pi³ kontakt z graczem
	void OnContact(Player &player);		//zachowanie przy kontakcie z graczem
	int startx;							//poczatkowa wspolrzedna x

protected:
	int movement;						//dlugosc trasy
	int damage;							//obrazenia zadawane graczowi
	Texture textable[6];				//tablica tekstur animacji
};

