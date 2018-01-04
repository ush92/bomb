#pragma once
#include <string>
#include <iostream>
#include "GameTypes.h"
#include "GameResources.h"

using namespace gameTypes;
using namespace std;

class Menu : public GameResources
{ 
public:
	Menu();
	~Menu(); 
	virtual void show() = 0;
	virtual GameScreen control() = 0;
protected:
	bool getIsActive() const;
	void setIsActive(bool state);
	void exit();	
	void animationxD();
	
	bool isActive;	
	GameScreen opt;
	ALLEGRO_COLOR color;
	ALLEGRO_EVENT events;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_KEYBOARD_STATE keyState;
};