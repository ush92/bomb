#include "Intro.h"


Intro::Intro(ALLEGRO_COLOR color)  
{
	this->color=color; //przypisanie kolorow tla
	setIsActive(true);
	al_start_timer(timer);
	animStep = -350;
	rand_x = float(rand()%704+64);
	speed = float(rand()%2+2);
}

Intro::~Intro(void)
{
}

void Intro::show()
{	
	al_draw_bitmap(getInstance()->resources->bitmap[B_SOFT_BRICK], rand_x,-40+animStep, NULL);
	al_draw_bitmap_region(getInstance()->resources->bitmap[B_PLAYER],int(rand_x)%3 * 32,0,32,32,rand_x,-72+animStep, NULL);
	al_draw_text(getInstance()->resources->font[F_BIG],al_map_rgb(0,0,0),410,37,ALLEGRO_ALIGN_CENTRE,"BOOMAN");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),90,300,ALLEGRO_ALIGN_INTEGER,"press any key...");
	al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_FRAME2],0,0,NULL);
	al_flip_display();	
	al_clear_to_color(al_map_rgb(70,70,70));
}

GameScreen Intro::control()
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

		if(events.type == ALLEGRO_EVENT_TIMER) 
		{
			animStep += speed;
			if(animStep > 832)
			{
				animStep = 0;
				rand_x = float(rand()%736+32);
				speed = float(rand()%5+4);
			}
		}

		if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{		
			al_flush_event_queue(event_queue);//czyszczenie bufora eventow. 
			opt = MAIN_MENU_SCREEN;
			goodOpt = true;
		}

		if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			al_play_sample(getInstance()->resources->sample[Sample::S_MENU_SELECT1], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			exit();
			al_stop_timer(timer);
			return opt;
		}

		show();
	}
	
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \nintro.control()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
 }



