#include "GameOver.h"


GameOver::GameOver(void)
{
}


GameOver::~GameOver(void)
{
}

void GameOver::show()
{
	al_play_sample(getInstance()->resources->sample[S_LIFE_LOST], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	al_rest(1.8);
	setIsActive(true);
	al_clear_to_color(al_map_rgb(30,130,190));
	al_draw_textf(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),400,275,ALLEGRO_ALIGN_CENTRE,"game over");
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),755,545,ALLEGRO_ALIGN_RIGHT,"press any key...");
	al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_FRAME2],0,0,NULL);
	al_flip_display();
}

GameScreen GameOver::control()
{
	bool goodOpt = false; //zmienna ktora zapobiega nieporządanym reakcjom na wybor opcji ktora nieistnieje/nie jest dostępna
	al_flush_event_queue(event_queue);//czyszczenie bufora eventow.
	while(isActive)
	{
		al_wait_for_event(event_queue, &events);
					
		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			exit(); //wyjscie za pomoca okienkowego przycisku X
			return NULL_SCREEN;
		}
		else if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{		 
			opt = MAIN_MENU_SCREEN;
			goodOpt = true;
		}
		else if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			al_play_sample(getInstance()->resources->sample[S_MENU_SELECT1], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			exit();
			return opt;
		}
	}
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \ngameover.control()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
}

