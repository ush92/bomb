#include "About.h"

About::About(ALLEGRO_COLOR color)  
{
	this->color=color; //przypisanie kolorow tla
}

About::~About(void)
{
}

void About::show()
{
	setIsActive(true);
	al_clear_to_color(color);
	al_draw_bitmap(getInstance()->resources->bitmap[Bitmap::B_BCK_FRAME2],0,0,NULL);
	
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),420,37,ALLEGRO_ALIGN_CENTRE,"about...");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,170,ALLEGRO_ALIGN_CENTER,"booman ver. 1.0 January 2014");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,285,ALLEGRO_ALIGN_CENTER,"author: mateusz trzyna");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,400,ALLEGRO_ALIGN_CENTER,"contact: ush1992@gmail.com");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),410,518,ALLEGRO_ALIGN_CENTRE,"A      - back");
	al_flip_display();
}

GameScreen About::control()
{
	bool goodOpt = false;	//zmienna ktora zapobiega nieporz¹danym reakcjom na wybor opcji ktora nieistnieje/nie jest dostêpna
	while(isActive)
	{	
		ALLEGRO_EVENT events;
		
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
				case ALLEGRO_KEY_A:		//jestesmy w About wiec nacisniecie A wraca do menu
					opt = MAIN_MENU_SCREEN;
					goodOpt = true;
					break;

				default:
					goodOpt = false;
					break;
			}
		}
		if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			al_play_sample(getInstance()->resources->sample[S_MENU_SELECT2], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			exit();
			return opt;
		}
	}
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \ncontrol()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
}
