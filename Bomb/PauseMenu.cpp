#include "PauseMenu.h"


PauseMenu::PauseMenu(ALLEGRO_COLOR color)
{
	this->color=color; //przypisanie kolorow tla
}


PauseMenu::~PauseMenu(void)
{
}

void PauseMenu::show()
{
	setIsActive(true);
	string pausetext = al_keycode_to_name(pauseKey);
	if(pauseKey == 63) pausetext = "bckspc"; //bo backspace jest za d³ugie i sie nie miesci -______-
	al_draw_filled_rectangle(0,0,800,600,color);
	al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_FRAME2],0,0,NULL);
	al_draw_text(getInstance()->resources->font[F_BIG],al_map_rgb(0,0,0),410,55,ALLEGRO_ALIGN_CENTRE,"PAUSE");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),80,250,ALLEGRO_ALIGN_INTEGER,pausetext.c_str());
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),369,250,ALLEGRO_ALIGN_INTEGER,"- RESUME");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),80,400,ALLEGRO_ALIGN_INTEGER,"Z");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),369,400,ALLEGRO_ALIGN_INTEGER,"- EXIT");
	al_flip_display();
}

GameScreen PauseMenu::control()
{
	al_flush_event_queue(event_queue);//czyszczenie bufora eventow. 
	bool goodOpt = false; //zmienna ktora zapobiega nieporz¹danym reakcjom na wybor opcji ktora nieistnieje/nie jest dostêpna
	while(isActive)
	{
		al_wait_for_event(event_queue, &events);
					
		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			setIsActive(false); //wyjscie za pomoca okienkowego przycisku X
			return NULL_SCREEN;
		}
		
		else if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{		
			//al_flush_event_queue(event_queue);//czyszczenie bufora eventow. 
			switch(events.keyboard.keycode)
			{				
				case ALLEGRO_KEY_Z:	//wyjscie do main menu
					opt = MAIN_MENU_SCREEN;
					al_play_sample(getInstance()->resources->sample[Sample::S_MENU_SELECT1], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					goodOpt = true;
					break;

				default:
					if(events.keyboard.keycode == pauseKey)
					{
						opt = CHALLENGE_SCREEN;
						goodOpt = true;	
					}
					else
					{
						goodOpt = false;
					}
					break;
			}
		}

		else if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			setIsActive(false);
			return opt;
		}
	}
	
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \nPause menu.control()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
 }

void PauseMenu::setPauseKey(int pauseKey)
{
	this->pauseKey = pauseKey;
}


