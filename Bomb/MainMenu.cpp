#include "MainMenu.h"

MainMenu::MainMenu(ALLEGRO_COLOR color)  
{
	this->color=color; //przypisanie kolorow tla
}

MainMenu::~MainMenu()
{
	
}

void MainMenu::show()
{
	setIsActive(true);
	al_clear_to_color(color);
	al_draw_bitmap(getInstance()->resources->bitmap[Bitmap::B_BCK_FRAME2],0,0,NULL);

	al_draw_text(getInstance()->resources->font[F_BIG],al_map_rgb(0,0,0),410,37,ALLEGRO_ALIGN_CENTRE,"BOOMAN");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,215,ALLEGRO_ALIGN_INTEGER,"1");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),269,215,ALLEGRO_ALIGN_INTEGER,"- PLAY"); //musi byc rozdzielone bo inaczej jest krzywo
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,300,ALLEGRO_ALIGN_INTEGER,"Q      - settings");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,385,ALLEGRO_ALIGN_INTEGER,"A      - ABOUT");
	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),110,470,ALLEGRO_ALIGN_INTEGER,"Z      - QUIT");
	al_flip_display();
}

GameScreen MainMenu::control()
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
		else if(events.type == ALLEGRO_EVENT_KEY_DOWN)	//wcisnij i trzymaj klawisz - zapamietaj opcje
		{		
			al_flush_event_queue(event_queue);//czyszczenie bufora eventow. 
			switch(events.keyboard.keycode)
			{
				case ALLEGRO_KEY_A:	//about...
					opt = ABOUT_SCREEN;
					goodOpt = true;
					break;

				case ALLEGRO_KEY_Z:	//wyjscie
					opt = NULL_SCREEN;
					goodOpt = true;
					break;

				case ALLEGRO_KEY_Q:	//opcje gry!!!
					opt = OPTIONS_SCREEN;
					goodOpt = true;
					break;

				case ALLEGRO_KEY_1:	//start gry!!!
					opt = CHALLENGE_SCREEN;
					goodOpt = true;
					break;

				default:
					goodOpt = false;
					break;
			}
		}
		else if(events.type == ALLEGRO_EVENT_KEY_UP && goodOpt)		//pusc klawisz - teraz zostanie wywolana funkcja
		{
			al_play_sample(getInstance()->resources->sample[Sample::S_MENU_SELECT1], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			exit();
			return opt;
		}
	}
	
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \ncontrol()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
 }
