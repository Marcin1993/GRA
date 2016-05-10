//Character.h
//klasa abstrakcyjna, zawiera pola i metody postaci
#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Character: public Drawable, Transformable
{
public:
	Character(void);				
	virtual ~Character(void);
										//mo¿liwe stany postaci
	enum CharacterState{
		GO_LEFT,
		GO_RIGHT,
		DEAD,
	};
	CharacterState status;				//obecny stan postaci
	virtual void GoRight() = 0;			//ruch w prawo
	virtual void GoLeft() = 0;			//ruch w lewo
	virtual void update() = 0;			//aktualizacja animacji
	Vector2f GetPosition();				//zwraca aktualn¹ pozycjê postaci
	FloatRect GetGlobalBounds();		//zwraca prostok¹t w którym znajduje siê postaæ
	int getSpeed();						//zwraca prêdkoœæ
	void PlaceCharacter(int x, int y);	//ustawia postaæ na pozycji (x,y)

protected:
	Sprite sprite;						//sprite postaci
	int speed;							//prêdkoœæ poruszania
	int i;								//iterator animacji

	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const; //rysuj sprite'a
};
