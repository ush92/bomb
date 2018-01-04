#pragma once
#include "Menu.h"

class About :
	public Menu
{
public:
	About(ALLEGRO_COLOR color);
	~About(void);
	void show() override;
	GameScreen control();
};

