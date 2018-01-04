#include "AllegroForm.h"

AllegroForm::AllegroForm(char* windowTitle)
{
	if(!al_init())
	{
		al_show_native_message_box(NULL, "Game", "Error", "Failed to start Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}
	al_set_new_display_flags(ALLEGRO_WINDOWED); //opcje okna
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	al_set_window_position(display,283,84);
	al_set_window_title(display, windowTitle);
	al_hide_mouse_cursor(display);

	al_init_primitives_addon(); //wczytanie ró¿nych fajnych rzeczy
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon(); //kodek do dzwieku
	al_init_font_addon(); 
	al_init_ttf_addon();
	al_init_image_addon();
	icon = al_load_bitmap("icon.png");
	al_set_display_icon(display, icon);
	al_reserve_samples(1);
}

AllegroForm::~AllegroForm(void)
{
	al_destroy_bitmap(icon);
	al_destroy_display(display);
}
