#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <string>
#include "GameTypes.h"
#include "Map.h"
#include "Bomb.h"
#include "Monster.h"
#include "RoundLoader.h"
#include "GameResources.h"

using namespace std;

class Round: 
	public GameResources
{
public:
	Round(void);
	~Round(void);
	void playTheme();
	void Round::stopTheme();
	Map* getMap() const;
	void setLevelItemState(bool state);
	bool getLevelItemState();

	bool questDone();

	Monster* getMonster(int id) const;

	int getID() const;
	void setID(int id);
	void createName(int id);
	string getName() const;

	void setTimeLeft(float timeLeft);
	void decrementTime();
	float getTimeLeft() const;
	void createLowTimeEvent();
	
	void reset();

	void setMonstersCount(int monstersCount); 
	int getMonstersCount() const;
	
	void setActiveMonsters(int activeMonsters);
	int getActiveMonsters();

private:
	void respawnMonsters();
	
	Map* map; 
	RoundLoader* loadingScreen;
	
	int ID;
	string name;
	ALLEGRO_SAMPLE_INSTANCE *roundTheme;
	ALLEGRO_SAMPLE_INSTANCE *lowTimeTheme;

	Monster* monster[6];
	ItemType levelItem; 
	MonsterType levelMonster;
	
	bool levelItemState;
	int monstersCount;
	int activeMonsters; 
	float timeLeft; 
	bool lowTimeEvent; 
	bool lastMonsterSound; 
};


