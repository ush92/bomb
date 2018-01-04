#include "SetControls.h"


SetControls::SetControls(ALLEGRO_COLOR color)
{
	this->color = color; //przypisanie kolorow tla
}


SetControls::~SetControls(void)
{
}

GameControls SetControls::getNewControlOptions() const
{
	return controlOpt;
}

void SetControls::show()
{
	setIsActive(true);
	al_clear_to_color(color);
	al_draw_bitmap(getInstance()->resources->bitmap[Bitmap::B_BCK_FRAME2],0,0,NULL);

	al_draw_text(getInstance()->resources->font[F_NORMAL],al_map_rgb(0,0,0),400,37,ALLEGRO_ALIGN_CENTRE,"SET CONTROLS");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,135,ALLEGRO_ALIGN_CENTRE,"press buttons to set");
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),100,220,ALLEGRO_ALIGN_LEFT,"UP              "); 
	
	al_flip_display();
}

void SetControls::displayOptions(int y, string key,string text,float pitch)
{
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),700,y,ALLEGRO_ALIGN_RIGHT,key.c_str()); 
	al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),100,y+50,ALLEGRO_ALIGN_LEFT,text.c_str());
	al_reserve_samples(3);
	al_play_sample(getInstance()->resources->sample[Sample::S_MENU_SELECT1], 1.2, 0.0, pitch, ALLEGRO_PLAYMODE_ONCE, 0);
	al_reserve_samples(1);
	al_flip_display();
}

GameScreen SetControls::control() 
{
	bool goodOpt = false;	//zmienna ktora zapobiega nieporz¹danym reakcjom na wybor opcji ktora nieistnieje/nie jest dostêpna
	bool isAllSet = false;
	bool isUnique = true;
	int i=0; //licznik ustawiania opcji. gdy beidze = 7 i wszystko jest ustawione dobrze isAllSet zrobi siê na true i petla sie przerwie
	int keyCode[7]={-1,-2,-3,-4,-5,-6,-7}; //przechowuje kod wcisnietego klawisza. domyœlnie wartoœci ktore nie odpowiadaja zadnemu klawiszowi
	string keyName; //przechowuje nazwê wcisnietego klawisza
	
	while(isActive)
	{
		while(!isAllSet)
		{	
			ALLEGRO_EVENT events;
		
			al_wait_for_event(event_queue, &events);
			
			if(events.type == ALLEGRO_EVENT_KEY_DOWN)	
			{
				al_flush_event_queue(event_queue);//czyszczenie bufora eventow z porzedniego sccreena
			}
			else if(events.type == ALLEGRO_EVENT_KEY_UP)
			{
				
				if(i<7)//zapisuj dane tylko dla pierwszych 6 klawiszy. potem ignoruj
				{
					keyCode[i] = events.keyboard.keycode;
					keyName = al_keycode_to_name(keyCode[i]);
					if(i) //pomin pierwsza iteracje (nie mozna sprawdzic duplikatu skoro jest 1 element)
					{
						for(int k=1;k<=i;k++)
						{
							if(keyCode[i]==keyCode[i-k])
							{
								isUnique = false;
							}
						}
					}
				}

				if(isUnique) //jezeli wybrany znak jest unikalny
				{
					switch(i)
					{
						case 0: //up
							controlOpt.up = keyCode[i];
							displayOptions(220,keyName,"DOWN              ", 0.7);
							break;
					
						case 1://down
							controlOpt.down = keyCode[i];	
							displayOptions(270,keyName,"LEFT              ", 0.8);
							break;

						case 2://left
							controlOpt.left = keyCode[i];
							displayOptions(320,keyName,"RIGHT              ", 0.9);
							break;
					
						case 3://right
							controlOpt.right = keyCode[i];	
							displayOptions(370,keyName,"BOMB              ", 1.0);
							break;
				
						case 4://bomb
							controlOpt.bomb = keyCode[i];	
							displayOptions(420,keyName,"DETONATE              ", 1.1);
							break;

						case 5://detonate
							controlOpt.detonate = keyCode[i];	
							displayOptions(470,keyName,"PAUSE              ", 1.2);
							break;
				
						case 6://pause
							controlOpt.pause = keyCode[i];	
							displayOptions(520,keyName,"", 1.3);
							al_draw_text(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),400,315,ALLEGRO_ALIGN_CENTER,"DONE!!");
							al_flip_display();
							break;

						default://DONE!!
							break;
					}
				
					i++; //przypisanie jednego klawisza zostalo wykonane, licznik ++
					al_flush_event_queue(event_queue);
					if(i==8) //przypisanie zostalo zakonczone, wroc do viewControlScreen
					{
						al_play_sample(getInstance()->resources->sample[S_MENU_SELECT1], 1.2, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, 0);
						exit();
						return VIEW_CONTROL_SCREEN; 
					}
				}
				else //isUnique jest falszem! Znak zostal juz uzyty!! wybierz inny znak
				{
					al_play_sample(getInstance()->resources->sample[S_PUT_BOMB_ERR], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					isUnique = true;//dajmy userowi jeszcze jedn¹ szansê na wprowadzenie poprawnych danych... 
				}
			}
		}	
	}
	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \ncontrol()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NULL_SCREEN; //dzieki temu nie ma warningow. generalnie funkcja nigdy tu nie powinna dojsc
}
