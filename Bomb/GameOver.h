#pragma once
#include "menu.h"
class GameOver :
	public Menu
{
public:
	GameOver();
	~GameOver(void);
	void show();
	GameScreen control();
	void set(int roundId, string name);
private:
	int roundId;
	string name;
};
