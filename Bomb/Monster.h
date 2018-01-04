#pragma once
#include "Player.h"
#include <cmath>

class Monster :
	public Character
{
public:
	Monster(void);
	~Monster(void);
	void draw();
	void setType(MonsterType id);
	void control(Map* map, Player* player);	
	bool killPlayer(Player* player);
	int getHealthPoints() const;
	void die();
private:
	MonsterType type;
	Bitmap bitmap;
	int healthPoints; 

	float step;	
	float maxStep; 
	void changeDirection();
	void changeDirection2(Player* pl);
};

