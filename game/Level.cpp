#include "Level.h"
#include "Bomb.h"
#include "Heart.h"
#include "Flag.h"
#include "Diamond.h"
#include "EnemySnail.h"
#include "EnemySlime.h"
#include "EnemyFly.h"
#include <Windows.h>
#include <fstream>
#include <string>

Level::Level(void)
{
	//wczytanie tekstur pól
	try
	{
		if(!tab[0].loadFromFile("data/images/tilemid.png"))
			throw string("data/images/tilemid.png");
		if(!tab[1].loadFromFile("data/images/tileleft.png"))
			throw string("data/images/tileleft.png");
		if(!tab[2].loadFromFile("data/images/tileright.png"))
			throw string("data/images/tileright.png");
		if(!tab[3].loadFromFile("data/images/tileng.png"))
			throw string("data/images/tileng.png");
		if(!tab[4].loadFromFile("data/images/empty.png"))
			throw string("data/images/empty.png");
	}
	catch(string ex)
	{
		string tmp = "Texture not found: " + ex;
		MessageBox(NULL,tmp.c_str(),"ERROR",NULL);
		exit(1);
	}
}

Level::~Level(void)
{
	for(int i = envec.size()-1; i>=0 ;i = envec.size()-1 )
	{
		delete envec[i];
		envec.pop_back();
	}
	for(int i = itvec.size()-1; i>=0 ;i = itvec.size()-1 )
	{
		delete itvec[i];
		itvec.pop_back();
	}
}

bool Level::loadFromFile(string filename)
{
	fstream file("data/levels/"+filename, ios::in);
	try
	{
		if(!file.is_open()) throw string(filename);
	}
	catch(string ex)
	{
		return false;
	}
	
	for(int i=0;i<height;i++)	//wczytanie danych poziomu z pliku wraz z wype³nieniem charakt
	{
		for(int j=0;j<width;j++)
		{
			int tmp;
			file >> tmp;
 
			if(tmp == 0) //sciana
			{
				lvldata[i][j].isFloor = false;
				lvldata[i][j].type = FIELD_WALL;
				lvldata[i][j].sprite.setPosition(40*j, 40*i);	
				lvldata[i][j].sprite.setTexture(tab[4]);
			}	
			else if(tmp ==1) //srodek platformy
			{	
				lvldata[i][j].isFloor = true;
				lvldata[i][j].type = FIELD_FLOORM;
				lvldata[i][j].sprite.setPosition(40*j, 40*i);
				lvldata[i][j].sprite.setTexture(tab[0]);
			}
			else if(tmp ==2) //lewa krawedz platformy
			{	
				lvldata[i][j].isFloor = true;
				lvldata[i][j].type = FIELD_FLOORL;
				lvldata[i][j].sprite.setPosition(40*j, 40*i);
				lvldata[i][j].sprite.setTexture(tab[1]);
			}
			else if(tmp ==3) //prawa krawedz platformy
			{	
				lvldata[i][j].isFloor = true;
				lvldata[i][j].type = FIELD_FLOORR;
				lvldata[i][j].sprite.setPosition(40*j, 40*i);
				lvldata[i][j].sprite.setTexture(tab[2]);
			}
			else if(tmp ==4) //podloze nie szczyt
			{	
				lvldata[i][j].isFloor = true;
				lvldata[i][j].type = FIELD_FLOORNG;
				lvldata[i][j].sprite.setPosition(40*j, 40*i);
				lvldata[i][j].sprite.setTexture(tab[3]);
			}
		}
	}
 
	file.close();
	return true;
}

bool Level::loadEnemyList(string filename)
{
	fstream file("data/levels/"+filename, ios::in);
	try
	{
		if(!file.is_open()) throw string(filename);
	}
	catch(string ex)
	{
		return false;
	}

	Enemy *temp; //tymczasowa zmienna, reprezentuje przeciwnika

	for(int i=0;i<height;i++)	//wczytywanie przeciwników do wektora
	{
		for(int j=0;j<width;j++)
		{
			int tmp;
			file >> tmp;
 
			if(tmp == 1) //snail
			{
				temp = new EnemySnail;
			}
			else if(tmp == 2) //slime
			{
				temp = new EnemySlime;
			}
			else if(tmp == 3) //fly
			{
				temp = new EnemyFly;
			}
			else continue;

			(*temp).startx = 40*j;
			(*temp).PlaceCharacter(40*j, 40*i+10);
			envec.push_back(temp);
		}
	}
	return true;
}

bool Level::loadItemList(string filename)
{
	fstream file("data/levels/"+filename, ios::in);
	try
	{
		if(!file.is_open()) throw string(filename);
	}
	catch(string ex)
	{
		return false;
	}

	Item *temp; //tymczasowa zmienna, reprezentuje przedmiot

	for(int i=0;i<height;i++)	//wczytywanie przedmiotów do wektora
	{
		for(int j=0;j<width;j++)
		{
			int tmp;
			file >> tmp;
 
			if(tmp == 1) //flag
			{
				temp = new Flag;
			}
			else if(tmp == 2) //heart
			{
				temp = new Heart;
			}
			else if(tmp == 3) //diamond
			{
				temp = new Diamond;
			}
			else if(tmp == 4) //bomb
			{
				temp = new Bomb;
			}
			else continue;

			(*temp).PlaceItem(40*j, 40*i);
			itvec.push_back(temp);
		}
	}
	return true;
}