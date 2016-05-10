#include "Engine.h"
#include "Level.h"
#include <math.h>
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
using namespace sf;

Engine::Engine(RenderWindow &win){

	Level *tmp;

	window = &win;

	bgd.loadFromFile("data/images/BackgroundSky.jpg");
	background.setTexture(bgd);
	hud = new HUD(player);

	for(int i = 0; ; i++){
		tmp = new Level;
		try
		{
			if(!(*tmp).loadFromFile("LVL"+to_string(i+1)+".txt")) throw 1;
			if(!(*tmp).loadEnemyList("E_LVL"+to_string(i+1)+".txt")) throw 1;
			if(!(*tmp).loadItemList("I_LVL"+to_string(i+1)+".txt")) throw 1;
			levels.push_back(tmp);
		}
		catch(int ex)
		{
			delete tmp;
			break;
		}
	}
	it = 0;
}

Engine::~Engine(void)
{
	for(int i = levels.size()-1; i>=0 ;i = levels.size()-1 )
	{
		delete levels[i];
		levels.pop_back();
	}
	delete hud;
}

void Engine::RunEngine()
{
	bool menu = false;
	(*window).setVerticalSyncEnabled(true);

	ShowCursor(false);

	while(menu == false){
	
		Event event;

		//sprawdzenie czy iterator poziomów nie przekracza liczby poziomów
		if(it >= levels.size())
		{
			EndScreen(*window, *hud);
			it = 0;
			menu = true;
			continue;
		}
		else level = levels[it];

		//ustawienie gracza w przypadku zmiany poziomu
		if((*hud).changeflag == 1)
		{
			player.PlaceCharacter(0,520);
			(*hud).changeflag = 0;
		}

		//obs³uga klawiszy ruchu:
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			if(collisionSide() == false) player.GoRight();
		}
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			if(collisionSide() == false) player.GoLeft();
		}
		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			if(collisionUp() == false && player.jumpflag == 0) player.GoUp();
		}
		if((Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::Up))==false) player.Stop();
		
		Jump();					//obsluga skoku
		gravity();				//grawitacja
		AnimationUpdate();		//aktualizacja animacji postaci

		//rysowanie ekranu gry
		window->clear();
		DrawAll();
		window->display();

		//sprawdzenie warunku wyjscia
		if(endgame() == true)
		{
			it = 0;
			menu = true;
			GameOver(*window);
		}
		//menu pauzy
		(*window).pollEvent(event);
		if(event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
		{ 
			if(pause(*window) == false) 
			{
				it = 0;
				menu = true;
			}
			else event.key.code = Keyboard::X;
		}
	}
}

void Engine::RunEngine(int m)
{
	it = m;
	RunEngine();
}

bool Engine::collisionSide()
{
	FloatRect playr = player.GetGlobalBounds();
	
	playr.width += player.getSpeed();
	playr.left -= player.getSpeed();
	playr.height -= player.getSpeed();

	for(int i = 0; i<Level::height; i++)
		for(int j = 0; j<Level::width; j++){
			FloatRect obiekt = (*level).lvldata[i][j].sprite.getGlobalBounds();
			if((*level).lvldata[i][j].type != Level::FIELD_WALL && playr.intersects(obiekt) == true) return true;
		}
	return false;
}

bool Engine::collisionUp()
{
	FloatRect playr = player.GetGlobalBounds();
	
	playr.height = 1;

	for(int i = 0; i<Level::height; i++)
		for(int j = 0; j<Level::width; j++){
			FloatRect obiekt = (*level).lvldata[i][j].sprite.getGlobalBounds();
			if((*level).lvldata[i][j].type != Level::FIELD_WALL && playr.intersects(obiekt) == true) return true;
		}
	return false;
}

bool Engine::collisionDown()
{
	FloatRect playr = player.GetGlobalBounds();
	
	playr.top += (playr.height-1);
	playr.height = 1;

	for(int i = 0; i<Level::height; i++)
		for(int j = 0; j<Level::width; j++){
			FloatRect obiekt = (*level).lvldata[i][j].sprite.getGlobalBounds();
			if((*level).lvldata[i][j].type != Level::FIELD_WALL && playr.intersects(obiekt) == true) return true;
		}
	return false;
}

void Engine::gravity()
{
	if(collisionDown() == false){
		player.PushDown(player.getSpeed());
	}
}

bool Engine::endgame()
{
	if(player.health <= 0) return true;
	return false;
}

void Engine::GameOver(RenderWindow &window)
{
	Font font;
	Event event;
	font.loadFromFile("data/fonts/menu.ttf");
	Text text1("Game Over",font, 80);
	Text text2("Your score is: "+to_string((*hud).score), font, 60);
	text1.setPosition(1280/2-text1.getGlobalBounds().width/2, 300);
	text2.setPosition(1280/2-text2.getGlobalBounds().width/2, 400);
	window.clear();
	window.draw(text1);
	window.draw(text2);
	window.display();
	window.pollEvent(event);
	while(event.type != Event::TextEntered) window.pollEvent(event);
	return;
}

bool Engine::pause(RenderWindow &window)
{
	Font font;
	Event event;
	font.loadFromFile("data/fonts/menu.ttf");
	Text text1("Continue",font, 80);
	Text text2("Exit to main", font, 80);
	text1.setPosition(1280/2-text1.getGlobalBounds().width/2, 270);
	text2.setPosition(1280/2-text2.getGlobalBounds().width/2, 370);

	ShowCursor(true);

	while(true)
	{
		Vector2f mouse(Mouse::getPosition());
		window.pollEvent(event);
		//Wciœniêcie CONTINUE
		if(text1.getGlobalBounds().contains(mouse))
		{
			text1.setColor(Color::Cyan);
			text2.setColor(Color::White);
			if(event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				ShowCursor(false);
				return true;
			}
		}
		//Wciœniêcie EXIT TO MAIN
		else if(text2.getGlobalBounds().contains(mouse))
		{
			text2.setColor(Color::Cyan);
			text1.setColor(Color::White);
			if(event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				ShowCursor(false);
				return false;
			}
		}
		window.clear();
		window.draw(text1);
		window.draw(text2);
		window.display();
	}
}

void Engine::EndScreen(RenderWindow &window, HUD &hud)
{
	Font font;
	Event event;
	font.loadFromFile("data/fonts/menu.ttf");
	Text text1("YOU WIN!",font, 80);
	text1.setColor(Color::White);
	Text text2("Your score: "+to_string(hud.score), font, 60);
	text2.setColor(Color::White);
	Text text3("Press any key to continue", font, 40);
	text3.setColor(Color::White);

	text1.setPosition(1280/2-text1.getGlobalBounds().width/2, 270);
	text2.setPosition(1280/2-text2.getGlobalBounds().width/2, 370);
	text3.setPosition(1280/2-text3.getGlobalBounds().width/2, 600);

	window.clear();
	window.draw(text1);
	window.draw(text2);
	window.draw(text3);
	window.display();

	while(true)
	{
		window.pollEvent(event);
		if(event.type == Event::KeyPressed) return;
	}
}

void Engine::Jump()
{
	if(player.jumpflag == 1)
		{
			if(player.jumpspeed>0){
				player.PushUp(2*player.jumpspeed);
				player.jumpspeed -= 3;
			}
			else
			{
				if(collisionDown() == true)
				{
					player.jumpspeed = 28;
					player.jumpflag = 0;
				}
			}
		}
}

void Engine::AnimationUpdate()
{
	static Clock zegar; //zegar animacji gracza
	static Clock zegar2; //zegar animacji przeciwnkików

	//aktualizacja animacji gracza
	if(zegar.getElapsedTime() > seconds(0.05))
	{
		player.update();
		zegar.restart();
	}
	//aktualizacja animacji przeciwników
	if(zegar2.getElapsedTime() > seconds(0.08))
	{
		for(int j = 0; j < (*level).envec.size(); j++) (*((*level).envec[j])).update();
		zegar2.restart();
	}
}

void Engine::DrawMap()
{
	background.setPosition(0,0);
	window->draw(background);
	background.move(960,0);
	window->draw(background);

	for(int j=0; j<Level::height; j++){
		for(int k = 0; k<Level::width; k++)
		{
			window->draw((*level).lvldata[j][k].sprite);
		}
	}

}

void Engine::DrawEnemies()
{
	for(int j=0; j < (*level).envec.size(); j++)
	{
		window->draw(*((*level).envec[j]));
		//poruszanie przeciwnika i usuwanie z wektora przeciwnikow
		if((*((*level).envec[j])).Move()==false)
		{
			delete (*level).envec[j];
			(*level).envec.erase((*level).envec.begin()+j);
			j--;
			break;
		}
		//sprawdzenie kontaktu gracza z przeciwnikiem
		if((*((*level).envec[j])).status != Enemy::DEAD)
			if((*((*level).envec[j])).Contact(player))
				(*((*level).envec[j])).OnContact(player);
	}
}

void Engine::DrawItems()
{
	for(int j=0; j<(*level).itvec.size(); j++)
	{
		window->draw(*((*level).itvec[j]));
		if((*((*level).itvec[j])).Contact(player))
		{
			(*((*level).itvec[j])).Effect(*hud, it);
			delete (*level).itvec[j];
			(*level).itvec.erase((*level).itvec.begin()+j);
		}
	}
}

void Engine::DrawAll()
{
	DrawMap();
	DrawItems();
	DrawEnemies();
	(*hud).Draw(*window);
	window->draw(player);
}