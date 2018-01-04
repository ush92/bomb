#include "ViewControls.h"


ViewControls::ViewControls(ALLEGRO_COLOR color)
{
	this->color = color; //przypisanie kolorow tla
}


ViewControls::~ViewControls(void)
{
}

void ViewControls::setNewControlOptions(GameControls controlOpt)
{
	this->controlOpt.up = controlOpt.up;
	this->controlOpt.down = controlOpt.down;
	this->controlOpt.left = controlOpt.left;
	this->controlOpt.right = controlOpt.right;
	this->controlOpt.bomb = controlOpt.bomb;
	this->controlOpt.detonate = controlOpt.detonate;
	this->controlOpt.pause = controlOpt.pause;
}

void ViewControls::show()
{
	setIsActive(true);
	al_clear_to_color(color);
	al_draw_bitmap(getInstance()->resources->bitmap[Bitmap::B_BCK_FRAME2],0,0,NULL);

	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),400,37,ALLEGRO_ALIGN_CENTRE,"SET CONTROLS");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,120,ALLEGRO_ALIGN_CENTRE,"s - set");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,165,ALLEGRO_ALIGN_CENTRE,"a - back");
	//wyswietlenie aktualnych ustawien sterowania
	displayOptions(220,al_keycode_to_name(controlOpt.up),"UP              ");
	displayOptions(270,al_keycode_to_name(controlOpt.down),"DOWN              ");
	displayOptions(320,al_keycode_to_name(controlOpt.left),"LEFT              ");
	displayOptions(370,al_keycode_to_name(controlOpt.right),"RIGHT              ");
	displayOptions(420,al_keycode_to_name(controlOpt.bomb),"BOMB              ");
	displayOptions(470,al_keycode_to_name(controlOpt.detonate),"DETONATE              ");
	displayOptions(520,al_keycode_to_name(controlOpt.pause),"PAUSE              ");
	al_flip_display();
}

GameScreen ViewControls::control()
{
	bool goodOpt = false;	//zmienna ktora zapobiega nieporz¹danym reakcjom na wybor opcji ktora nieistnieje/nie jest dostêpna
	while(isActive)
	{	
		ALLEGRO_EVENT events;
		
		al_flush_event_queue(event_queue);
		al_wait_for_event(event_queue, &events);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			exit(); //wyjscie za pomoca okienkowego przycisku X
			return NULL_SCREEN;
			break;
		}
		if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{
			al_flush_event_queue(event_queue);//czyszczenie bufora eventow. 
			switch(events.keyboard.keycode)
			{
				case ALLEGRO_KEY_A:		//jestesmy w ViewControlsScreen wiec nacisniecie A wraca do Options
					opt = OPTIONS_SCREEN;
					goodOpt = true;
					break;

				case ALLEGRO_KEY_S:
					opt = SET_CONTROL_SCREEN;
					goodOpt = true;
					break;

				default:
					goodOpt = false;
					break;
			}
		}
		if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			if(opt == SET_CONTROL_SCREEN)
			{
				al_play_sample(getInstance()->resources->sample[S_MENU_SELECT1], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else al_play_sample(getInstance()->resources->sample[S_MENU_SELECT2], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			exit();
			return opt;
		}
	}
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \ncontrol()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
}

void ViewControls::displayOptions(int y, string key,string text)
{
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),700,y,ALLEGRO_ALIGN_RIGHT,key.c_str()); 
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),100,y,ALLEGRO_ALIGN_LEFT,text.c_str());
	al_flip_display();
}

