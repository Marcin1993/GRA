//Level.h
//Przechowuje dane poziomów oraz odpowiada za ich wczytywanie
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
											//typy pól mapy
	enum FieldType 
	{
		FIELD_FLOORL,
		FIELD_FLOORR,
		FIELD_FLOORM,
		FIELD_FLOORNG,
		FIELD_WALL,
	};
											//charakterystyka pól
	struct Data
	{
		FieldType type;
		Sprite sprite;
		bool isFloor;
	};
	
	Texture tab[5];							//tablica tekstur pól
	static const int width = 32;			//szerokoœæ poziomu
	static const int height = 18;			//wysokoœæ poziomu
	Data lvldata[height][width];			//tablica pól poziomu
	vector<Enemy*> envec;					//lista przeciwników
	vector<Item*> itvec;					//lista przedmiotów
	bool loadFromFile(string filename);		//wczytanie poziomu z pliku tekstowego filename
	bool loadEnemyList(string filename);	//wczytanie listy przeciwników z pliku filename
	bool loadItemList(string filename);		//wczytanie listy przedmiotów z pliku filename
 };
