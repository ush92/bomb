#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <string>
#include <array>
#include "GameTypes.h"
#include "Round.h"

using namespace gameTypes;
using namespace std;

class Interface : GameResources
{

public:
	Interface();
	~Interface(void);
	void show(float scrollPx) const;
	void update(float scrollPx, int roundID, int points, float timeLeft, string roundName, bool equipment, int monsterLeft, int hp);
	void setInterface(int roundID);
private:
	ALLEGRO_COLOR color; 
	ALLEGRO_COLOR color2; 
	int itemCount; 
	string itemName;
	string roundText1;
	string roundText2;
	Bitmap itemBitmap;
	Bitmap monBitmap;
};

