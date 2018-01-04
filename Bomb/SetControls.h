#pragma once
#include "Menu.h"
class SetControls :
	public Menu
{
public:
	SetControls(ALLEGRO_COLOR color);
	~SetControls(void);
	GameControls getNewControlOptions() const; 
	void show();
	GameScreen control();
private:
	void displayOptions(int y, string key, string text, float pitch);
	GameControls controlOpt;
};

