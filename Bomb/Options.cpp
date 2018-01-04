#include "Options.h"

Options::Options(ALLEGRO_COLOR color, bool soundOpt)  
{
	this->color=color; //przypisanie kolorow tla
	this->soundOpt = soundOpt;
}


Options::~Options(void)
{
}

bool Options::getNewSoundOptions() const
{
	return soundOpt;
}

void Options::show()
{
	setIsActive(true);
	al_clear_to_color(color);
	al_draw_bitmap(getInstance()->resources->bitmap[Bitmap::B_BCK_FRAME2],0,0,NULL);

	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),410,37,ALLEGRO_ALIGN_CENTRE,"settings");
	if(soundOpt) al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,215,ALLEGRO_ALIGN_LEFT,"s      - sound on");
	else al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,215,ALLEGRO_ALIGN_LEFT,"s      - sound off");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,340,ALLEGRO_ALIGN_LEFT,"A      - controls");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,470,ALLEGRO_ALIGN_LEFT,"q      - back");
	al_flip_display();
}

GameScreen Options::control() 
{
	bool goodOpt = false; //zmienna ktora zapobiega nieporz¹danym reakcjom na wybor opcji ktora nieistnieje/nie jest dostêpna
	while(isActive)
	{
		al_wait_for_event(event_queue, &events);
					
		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			exit(); //wyjscie za pomoca okienkowego przycisku X
			return NULL_SCREEN;
		}

		if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{		
			al_flush_event_queue(event_queue);//czyszczenie bufora eventow. 
			switch(events.keyboard.keycode)
			{
				case ALLEGRO_KEY_Q:	//jestesmy w opcjach wiec Q wraca do main menu
					opt = MAIN_MENU_SCREEN;
					goodOpt = true;
					break;

				case ALLEGRO_KEY_S:	//w³/wyl dzwiek
					opt = OPTIONS_SCREEN; //pozostan na option screen
					goodOpt = true;				
					break;

				case ALLEGRO_KEY_A:	//ustawienia sterowania!!
					opt = VIEW_CONTROL_SCREEN;
					goodOpt = true;
					break;

				default:
					goodOpt = false;
					break;
			}
		}
		if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			if(opt == OPTIONS_SCREEN)//taka sytuacja oznacza ze zostal wylaczony lub wlaczony dzwiek
			{
				if(soundOpt)
				{
					al_set_mixer_gain(al_get_default_mixer(), 0);
				}
				else
				{
					al_set_mixer_gain(al_get_default_mixer(), 1);
				}
				soundOpt = !(soundOpt);
				setIsActive(false);	
				return opt;
			}
			if(opt == VIEW_CONTROL_SCREEN)
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



