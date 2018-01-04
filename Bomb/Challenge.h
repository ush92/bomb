#pragma once
#include "Interface.h"
#include "Round.h"
#include "GameResources.h"
#include "Player.h"
#include "Camera.h"
#include "PauseMenu.h"

#define MONSTER_COUNT 6

class Challenge:
	public GameResources
{
public:
	Challenge(void);
	~Challenge(void);
	
	void generateNewChallenge();
	GameScreen update();
	void setControls(GameControls controlOpt);
	
	float getPoints() const;
	
private:
	ALLEGRO_COLOR getRoundColor(int roundID) const;
	ItemType getRoundItem(int roundID) const; 
	void start();
	void resume();
	void exit(); 
	void clearNotUsed(); 
	
	void checkField();
	
	void roundDone();
	
	bool isChallengeDone;

	bool isActive; 
	bool isQuestDone;
	float points;
	
	GameControls controlOpt;
	ALLEGRO_EVENT events;
	ALLEGRO_TIMER *controlTimer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_KEYBOARD_STATE keyState;
	BombState bombState;
	bool explosionState;
	
	Interface* gameInterface;
	Round* round;
	Player* player;
	Camera* camera;
	PauseMenu* pauseMenu;
};

