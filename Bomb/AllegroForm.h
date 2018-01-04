#pragma once
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include "GameTypes.h"

class AllegroForm
{
public:
	AllegroForm(char* windowTitle);
	~AllegroForm(void);
private:
	ALLEGRO_DISPLAY *display; 
	ALLEGRO_BITMAP *icon;
};