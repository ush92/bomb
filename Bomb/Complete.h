#pragma once
#include "menu.h"
class Complete :
	public Menu
{
public:
	Complete(void);
	~Complete(void);
	void show();
	GameScreen control();
	void setPoints(float points);
private:
	int roundId;
	string name;
	float points;
};

