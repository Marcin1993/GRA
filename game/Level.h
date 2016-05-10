//Level.h
//Przechowuje dane poziom�w oraz odpowiada za ich wczytywanie
#pragma once

#include "Enemy.h"
#include "Item.h"
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class Level
{
public:
	Level(void);
	~Level(void);
											//typy p�l mapy
	enum FieldType 
	{
		FIELD_FLOORL,
		FIELD_FLOORR,
		FIELD_FLOORM,
		FIELD_FLOORNG,
		FIELD_WALL,
	};
											//charakterystyka p�l
	struct Data
	{
		FieldType type;
		Sprite sprite;
		bool isFloor;
	};
	
	Texture tab[5];							//tablica tekstur p�l
	static const int width = 32;			//szeroko�� poziomu
	static const int height = 18;			//wysoko�� poziomu
	Data lvldata[height][width];			//tablica p�l poziomu
	vector<Enemy*> envec;					//lista przeciwnik�w
	vector<Item*> itvec;					//lista przedmiot�w
	bool loadFromFile(string filename);		//wczytanie poziomu z pliku tekstowego filename
	bool loadEnemyList(string filename);	//wczytanie listy przeciwnik�w z pliku filename
	bool loadItemList(string filename);		//wczytanie listy przedmiot�w z pliku filename
 };
