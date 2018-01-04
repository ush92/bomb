#pragma once
#include <array>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include "GameTypes.h"
using namespace std; 
using namespace gameTypes;
class Resources
{
public:
	Resources(void);
	~Resources(void);
	array <ALLEGRO_BITMAP*, BITMAP_COUNT> bitmap;
	array <ALLEGRO_FONT*, FONT_COUNT> font;
	array <ALLEGRO_SAMPLE*, SAMPLE_COUNT> sample;
};

