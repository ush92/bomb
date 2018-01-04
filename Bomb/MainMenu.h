#pragma once
#include "Menu.h"

class MainMenu:
	public Menu
{
public:
	MainMenu(ALLEGRO_COLOR color);
	~MainMenu(void);
	void show();
	GameScreen control();
};

