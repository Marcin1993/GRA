#include "Game.h"
#include "Engine.h"
#include <SFML\Graphics.hpp>

RenderWindow window(VideoMode(1280,720,32),"GameTitle", Style::Fullscreen);

Game::Game(void)
{ 
	try
	{
		if(!font.loadFromFile("data/fonts/menu.ttf"))
			throw string("data/fonts/menu.ttf");
	}
	catch(string ex)
	{
		ex = "Font not found: "+ex;
		state = END;
		MessageBox(NULL,ex.c_str(),"ERROR",NULL);
		exit(1);
	}
	state = MENU;
	it = 0;
}

Game::~Game(void)
{
}

void Game::RunGame(){
	while(state != END){
		switch(state){
			case GameState::MENU:
				menum();
				break;
			case GameState::GAME:
				single();
				break;
			case GameState::LOAD:
				load();
				break;
		}
	}
}

void Game::menum()
{
	Text title("GameTitle",font,80);
	title.setStyle(Text::Bold);
 
	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);
 
	const int ile = 3;
 
	Text tekst[ile];
 
	string str[] = {"New Game","Select Level", "Exit"};

	for(int i=0;i<ile;i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);
		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);
	}

	while(ShowCursor(false) < 0)
	{
		ShowCursor(true);
		ShowCursor(true);
	}
 
	while(state == MENU)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;
 
		while(window.pollEvent(event))
		{
			//Wciœniêcie New Game
			if(tekst[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = GAME;
			//Wciœniêcie LOAD GAME
			else if(tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = LOAD;
			//klikniêcie EXIT
			else if(tekst[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = END;
			//Wciœniêcie ESC lub przycisk X
			else if(event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = END;
		}

		for(int i=0;i<ile;i++)
			if(tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Cyan);
			else tekst[i].setColor(Color::White);
 
		window.clear();
 
		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);
 
		window.display();
	}
}

void Game::single(){
	Engine engine(window);

	engine.RunEngine(it);
	state = MENU;
}

void Game::load()
{
	vector<Level*> levels;
	Level *tmp;
	Text arrowl("<=",font,120);
	Text arrowr("=>",font,120);
	Text txt("Level 1", font, 120);
	Text back("Back", font, 70);
	back.setPosition(50, 500);
	Text OK("OK", font, 70);
	OK.setPosition(1280-OK.getGlobalBounds().width - 50, 500);
	Event event;

	for(int i = 0; ; i++)
	{
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

	while(state == LOAD)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;
		string tekst;
 
		while(window.pollEvent(event))
		{
			//Wciœniêcie strz³ki w lewo
			if(arrowl.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if(it <= 0) it = levels.size()-1;
				else --it;
			}
			//Wciœniêcie strza³ki w prawo
			else if(arrowr.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if(it>=levels.size()-1) it = 0;
				else ++it;
			}
			//Wciœniêcie back - powrót do menu
			else if(back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				it = 0;
				state = MENU;
			}
			//Wciœniêcie OK - rozpoczêcie gry
			else if(OK.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				single();
				it=0;
				state = MENU;
			}
		}
		if(state != MENU){
			tekst = "Level "+to_string(it+1);
			txt.setString(tekst);
			txt.setPosition(1280/2-txt.getGlobalBounds().width/2, 720/2-txt.getGlobalBounds().height/2-200);
			arrowr.setPosition(txt.getGlobalBounds().left + txt.getGlobalBounds().width + 30, 720/2-arrowr.getGlobalBounds().height/2-200);
			arrowl.setPosition(txt.getGlobalBounds().left - arrowl.getGlobalBounds().width - 30, 720/2-arrowl.getGlobalBounds().height/2-200);

			window.clear();
 
			window.draw(arrowl);
			window.draw(txt);
			window.draw(arrowr);
			window.draw(back);
			window.draw(OK);
 
			window.display();
		}
	}
	for(int i = levels.size()-1; i>=0 ;i = levels.size()-1 )
	{
		delete levels[i];
		levels.pop_back();
	}
}