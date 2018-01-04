#pragma once
#include "Menu.h"
class ViewControls :
	public Menu
{
public:
	ViewControls(ALLEGRO_COLOR color);
	~ViewControls(void);
	void setNewControlOptions(GameControls controlOpt); 
	void show();
	GameScreen control();
private:
	void displayOptions(int y, string key, string text);
	GameControls controlOpt;
};

