#pragma once
#include "menu.h"
class Intro :
	public Menu
{
public:
	Intro(ALLEGRO_COLOR color);
	~Intro(void);
	void show();
	GameScreen control();
private:
	float animStep;
	float rand_x;
	float speed;
};

