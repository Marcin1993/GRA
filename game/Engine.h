//Engine.h
//obs�uga wy�wietlania, mechaniki i fizyki
#pragma once
#include "Player.h"
#include "Level.h"
#include "HUD.h"

class Engine
{
public:
	Engine(RenderWindow &win);
	~Engine(void);

	void RunEngine(int m);					//uruchomienie silnika gry z wartosci� pocz�tkow�
	void RunEngine();						//uruchomienie silnika gry
	Player player;
	vector<Level*> levels;					//wektor poziom�w
	Level *level;							//aktualny poziom
	HUD *hud;							
	int it;									//iterator wektora poziom�w
private:
	RenderWindow *window;					//okno gry
	Texture bgd;
	Sprite background;
	
	bool collisionSide();					//kolizja boczna
	bool collisionUp();						//kolizja g�rna
	bool collisionDown();					//kolizja dolna
	void Jump();							//obs�uga skoku
	void gravity();							//grawitacja - gracz
	void AnimationUpdate();					//aktualizacja animacji gracza i przeciwnik�w
	void DrawMap();							//rysowanie mapy
	void DrawEnemies();						//rysowanie przeciwnikow
	void DrawItems();						//rysowanie przedmiotow
	void DrawAll();							//rysowanie calego ekranu
	bool endgame();							//czy koniec gry
	void GameOver(RenderWindow &window);	//ekran koncowy - smierc
	bool pause(RenderWindow &window);		//menu pauzy
	void EndScreen(RenderWindow &window, HUD &hud);	//ekran koncowy - ukonczenie gry
};

