#include "RoundLoader.h"


RoundLoader::RoundLoader()
{
	
}

RoundLoader::~RoundLoader(void)
{

}

void RoundLoader::set(int roundId, string name)
{
	this->roundId = roundId;
	this->name = name;
	switch(roundId)
	{
		case 1:
			color = al_map_rgb(105,140,117); //zielony
			break;
		case 2:
			color = al_map_rgb(105,129,140); //niebieski
			break;
		case 3:
			color = al_map_rgb(123,99,122); //fioletowy
			break;
		case 4:
			color = al_map_rgb(132,132,99); //zolty
			break;
		case 5:
			color = al_map_rgb(151,82,90); //czerwony
			break;
	}
}

void RoundLoader::show()
{
	setIsActive(true);
	al_clear_to_color(color);
	al_draw_textf(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),400,140,ALLEGRO_ALIGN_CENTRE,"stage %d",roundId);
	al_draw_textf(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),400,275,ALLEGRO_ALIGN_CENTRE,"%s",name.c_str());
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),755,545,ALLEGRO_ALIGN_RIGHT,"press any key...");
	al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_FRAME2],0,0,NULL);
	al_flip_display();	
	control();
}

GameScreen RoundLoader::control()
{
	bool goodOpt = false; //zmienna ktora zapobiega nieporz¹danym reakcjom na wybor opcji ktora nieistnieje/nie jest dostêpna
	while(isActive)
	{
		al_wait_for_event(event_queue, &events);
					
		if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{		
			al_flush_event_queue(event_queue);
			opt = NULL_SCREEN; 
			goodOpt = true;
		}

		if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			al_play_sample(getInstance()->resources->sample[S_MENU_SELECT1], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			exit();
			return opt;
		}
	}
	
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \nintro.control()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
}
