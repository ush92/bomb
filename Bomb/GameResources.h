#pragma once
#include "Resources.h"
#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h> 
#include "GameTypes.h"
using namespace std;
class GameResources 
{		
public:
	static GameResources* getInstance();
	Resources* resources;
protected:
	GameResources(void); 
	GameResources( const GameResources & ); 
	static bool instanceFlag;
	static GameResources *gameResources;
	~GameResources(void);
};

