#pragma once
#include "menu.h"
class RoundLoader :
	public Menu
{
public:
	RoundLoader();
	~RoundLoader(void);
	void show();
	GameScreen control();
	void set(int roundId, string name);
private:
	int roundId;
	string name;
};

