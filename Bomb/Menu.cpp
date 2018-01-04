#include "Menu.h"

Menu::Menu()
{
	setIsActive(false);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

Menu::~Menu(void)
{
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}

bool Menu::getIsActive() const
{
	return isActive;
}

void Menu::setIsActive(bool state)
{
	isActive = state;
}

void Menu::exit()
{
	setIsActive(false);
	animationxD();
}

void Menu::animationxD() //animacja przejscia miedzy scrreenami
{
	al_start_timer(timer);
	bool bAnim = true;
	bool draw=false;
	int i=0;
	while(bAnim)
	{
		al_wait_for_event(event_queue, &events);
		if(events.type == ALLEGRO_EVENT_TIMER) 
		{
			i+=15;
			if(i>250) bAnim=false;
			draw = true;
		}
					
		if(draw)
		{
			al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_FRAME2],0,0,NULL);
			al_draw_filled_rectangle(0,0,800,600,al_map_rgba(0,0,0,i)); //zwiekszanie alphy...
			al_flip_display();
			al_clear_to_color(color);					
		}	
	}
	al_stop_timer(timer);
}	




