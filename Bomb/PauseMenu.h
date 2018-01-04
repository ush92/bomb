#pragma once
#include "menu.h"
class PauseMenu :
	public Menu
{
public:
	PauseMenu(ALLEGRO_COLOR color);
	~PauseMenu(void);
	void show();
	GameScreen control();
	void setPauseKey(int pauseKey);
private:
	int pauseKey; 
};

