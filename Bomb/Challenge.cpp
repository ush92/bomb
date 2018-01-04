#include "Challenge.h"
#include <iostream>//test

using namespace std;//test

Challenge::Challenge(void)
{
	gameInterface = new Interface();
	round = new Round();
	player = new Player();
	pauseMenu = new PauseMenu(al_map_rgba(150,150,150,200));
	camera = new Camera();
	
	event_queue = al_create_event_queue();
	controlTimer = al_create_timer(1.0/FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(controlTimer));
	al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
}

Challenge::~Challenge(void)
{
	delete gameInterface;
	delete round;
	delete player;
	delete camera;
	delete pauseMenu;
	al_destroy_timer(controlTimer);
	al_destroy_event_queue(event_queue);
}

void Challenge::generateNewChallenge()
{
	isChallengeDone = false;
	
	pauseMenu->setPauseKey(controlOpt.pause);

	round->setID(1);
	for(int i=1;i<=5;i++)//usuniêcie itemów gracza
	{
		player->setEquipment(i,false); 
	}
	//player->setEquipment(1,false);
	isActive = true;
	points = 0;
	start();

	//round->getMap()->makeFree();//testOWAAAAAAAAAAAAAAAAAA!!
}

void Challenge::setControls(GameControls controlOpt)
{
	this->controlOpt.up = controlOpt.up;
	this->controlOpt.down = controlOpt.down;
	this->controlOpt.left = controlOpt.left;
	this->controlOpt.right = controlOpt.right;
	this->controlOpt.bomb = controlOpt.bomb;
	this->controlOpt.detonate = controlOpt.detonate;
	this->controlOpt.pause = controlOpt.pause;
}

ALLEGRO_COLOR Challenge::getRoundColor(int roundId) const
{
	switch(roundId)
	{
		case 1:
			return al_map_rgb(105,160,117); //zielony
			break;
		case 2:
			return al_map_rgb(105,129,150); //niebieski
			break;
		case 3:
			return al_map_rgb(123,99,132); //fioletowy
			break;
		case 4:
			return al_map_rgb(142,142,99); //zolty
			break;
		case 5:
			return al_map_rgb(161,82,90); //czerwony
			break;
	}
	return al_map_rgb(0,0,0);
}

ItemType Challenge::getRoundItem(int roundID) const
{
	switch(roundID)
	{
		case 1:
			return ITEM_L1; //roller-skates - wrotki +1mov speed
			break;
		case 2:
			return ITEM_L2; //d-napalm - zwieksza zasieg wybuchu o 1 pole
			break;
		case 3:
			return ITEM_L3; //electro fuse - pozwala na detonowanie ...
			break;
		case 4:
			return ITEM_L4; //spare bomb - bomba zapasowa
			break;
		case 5:
			return ITEM_L5; //dispersion suit - kombinezon rozproszeniowy :D przenikanie przez bomby i sciany
			break;
		default:
			return NO_ITEM;
			break;
	}
}

void Challenge::start() 
{
	player->reset();
	round->reset();
	isQuestDone = false;
	bombState = NO_BOMB;

	gameInterface->setInterface(round->getID());

	resume();
}

void Challenge::resume() 
{
	round->getMap()->draw(getRoundColor(round->getID()));		
	gameInterface->show(camera->getMapScrollPx());		
	player->draw();
	camera->repair();
	al_flip_display();	

	al_flush_event_queue(event_queue);
	al_start_timer(controlTimer);
}

void Challenge::exit()
{
	clearNotUsed();

	al_stop_timer(controlTimer);
	//round->reset();
	round->stopTheme();
	
	isActive = false;
	isQuestDone = false;

	for(int i=1;i<=5;i++)//usuniêcie itemów
	{
		player->setEquipment(i,false);
	}
	al_stop_samples();
}

GameScreen Challenge::update()
{
	GameScreen opt = NULL_SCREEN; //screen ktory moze zwrocic challenge
	bombState = NO_BOMB; //stan bomby
	bool redraw = true;  //rysowanie

	while(isActive)
	{
		al_wait_for_event(event_queue, &events);
		
		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //wyjscie za pomoca okienkowego przycisku X
		{
			exit(); 
			return NULL_SCREEN;
		}
		if(events.type == ALLEGRO_EVENT_TIMER)
		{			
			al_get_keyboard_state(&keyState);

			if(player->getIsActive())
			{
				if(al_key_down(&keyState, controlOpt.down))
				{			
				
					if(player->detectCollision(DOWN, round->getMap()))
					{		
						player->setAnimDir(DOWN);
						player->movDown();	
						player->animate();
						player->moveUDSound();
						redraw=true;					
					}
					else
					{
						player->setAnimDir(DOWN);
					}
				}
				else if(al_key_down(&keyState, controlOpt.up))
				{				
					if(player->detectCollision(UP, round->getMap()))
					{					
						player->setAnimDir(UP);
						player->movUp();
						player->animate();
						player->moveUDSound();
						redraw=true;
					}
					else
					{
						player->setAnimDir(UP);
					}
				}
				
				if(al_key_down(&keyState, controlOpt.right))
				{			
					if(player->detectCollision(RIGHT, round->getMap()))
					{
						player->setAnimDir(RIGHT);
						player->movRight();	
						player->animate();
						player->moveLRSound();
						redraw=true;					
					}
					else
					{
						//player->setAnimDir(RIGHT);	
					}
				}
				else if(al_key_down(&keyState, controlOpt.left))
				{
					if(player->detectCollision(LEFT, round->getMap()))
					{
						player->setAnimDir(LEFT);
						player->movLeft();
						player->animate();
						player->moveLRSound();
						redraw=true;
					}
					else
					{
					//	player->setAnimDir(LEFT);	
					}
				}
			}

			if(al_key_down(&keyState, controlOpt.pause)) //pauzaaa
			{
				al_stop_timer(controlTimer);
				camera->update(-(camera->getMapScrollPx())); //reset kamery
				pauseMenu->show();
				opt = pauseMenu->control();
					
				if(opt == CHALLENGE_SCREEN)
				{
					if(player->getX()<610)
					{
						camera->update(player->getX());//powrot kamery do poprzedniego stanu
					}
					else 
					{
						camera->update(607);//punkt w ktorym  kamera przestaje sie ruszac (od prawej strony)
					}
					resume(); //powort do gry
					redraw = true;
				}
				else if(opt == MAIN_MENU_SCREEN || opt == NULL_SCREEN) 
				{
					exit(); //wyjscie do main menu
					return opt;
				}	
			}
			else if(al_key_down(&keyState, ALLEGRO_KEY_F12) && al_key_down(&keyState, ALLEGRO_KEY_LSHIFT)) //nastêpna runda (tylko dla wersji beta :D)
			{
				player->setEquipment(round->getID(),true);
				roundDone();
				points = 0;
			}
				

			//ZDARZENIA ZALE¯NE TYLKO OD TIMERA:

			//cout<<player->getX()<<" "<<player->getY()<<endl; //testowe wsp gracza

			checkField();	//sprawdz czy zostal wziety item lub drzwi lub czy gracz wszedl w wybuch

			isQuestDone = round->questDone(); //czy cele misji zostaly wykonane

			for(int i = 0; i < MONSTER_COUNT; i++) //POTWORY
			{
				round->getMonster(i)->control(round->getMap(), player);	
				if(round->getMonster(i)->killPlayer(player)) player->die(); //potwor zabija gracza
				redraw = true;
				//cout<<int(round->getMonster(i)->getX()-16)/32<<" "<<int(round->getMonster(i)->getY()- 172)/32<<endl;
			}
	
			camera->update(player->getX()); 

			round->decrementTime();//odejmuje CZAS i zabija jesli sie skonczy
			if(round->getTimeLeft() <= 59)
			{
				round->createLowTimeEvent();

				if(round->getTimeLeft() <= 0)
				{
					player->die();
					round->setTimeLeft(0);
				}
			}		

			gameInterface->update(camera->getMapScrollPx(), round->getID(), points, round->getTimeLeft(), //INTERFEJS
				round->getName(), player->getEquipment(round->getID()), round->getActiveMonsters(), 
				round->getMonster(0)->getHealthPoints()); //odswiezanie elementów interfejsu
							
			if(bombState != NO_BOMB) // jeœli jakas bomba jest podlozona
			{
				if(bombState == ONE_BOMB) //zmieñ klatkê animacji bomby a dla trybu bez detonatora naliczaj czas bomby
				{
					player->getBomb(0)->animate();
					if(player->getBomb(0)->selfExplode() && !player->getEquipment(ITEM_L3))
					{
						int x0 = int(player->getBomb(0)->getX()-16)/32 - 1; //zamiana wspolrz na indexy mapy
						int y0 = int(player->getBomb(0)->getY()-172)/32 - 1;

/*wybuch+zmiana czasu*/ round->setTimeLeft(round->getTimeLeft() - round->getMap()->updateAfterExplosion(x0, y0, player->getEquipment(ITEM_L2) ? 2 : 1)); //update to float i zwraca czas do odjêcia w zaleznosci czy drzwi zostaly uderzone czy nie
						bombState = player->detonateBomb();
					}
				}
				else if(bombState == TWO_BOMBS)
				{
					player->getBomb(0)->animate();
					//!!!!  nie ma tu selfexplodów, poniewa¿ runda z detonatorem jest wczesniej niz z dodatkow¹ bomb¹   !!!!
					player->getBomb(1)->animate();
				}
		
				redraw=true;//odswiez animacje
			}	

			if(round->getMap()->getisBurning())//sprawdzenie czy coœ siê pali i w³¹czenie animacji (owa animacja jest w klasie map)
			{
				redraw = true; 
			}
		}
		
		if(events.type == ALLEGRO_EVENT_KEY_DOWN) //opcje jednego wcisniecia
		{			
			int x0,y0,x1,y1; //pomocnicze do czytelniejszego zapisu
			
			if(events.keyboard.keycode == controlOpt.bomb && player->getIsActive()) //BOMBA
			{
				bombState = player->putBomb(player->getX(), player->getY());//postaw bombe na wspol. gracza(funkcja put normalizuje te wspolrzedne)

				x0 = int(player->getBomb(bombState - 1)->getX()-16)/32 - 1; //zamiana wspolrz na indexy mapy
				y0 = int(player->getBomb(bombState - 1)->getY()-172)/32 - 1;
				round->getMap()->getField(x0,y0)->setIsFree(player->getEquipment(ITEM_L4));//jesli gracz ma item z rundy 4 to bomba nie robi kolizji
			} 

			if(events.keyboard.keycode == controlOpt.detonate && player->getEquipment(ITEM_L3) && player->getIsActive()) //detonacja bomby przyciskiem (tylko jesli gracz ma item 2)
			{
				if(bombState != NO_BOMB)
				{
					x0 = int(player->getBomb(0)->getX()-16)/32 - 1; //zamiana wspolrz na indexy mapy
					y0 = int(player->getBomb(0)->getY()-172)/32 - 1;
/*wybuch+zmiana czasu*/ round->setTimeLeft(round->getTimeLeft() - round->getMap()->updateAfterExplosion(x0, y0, player->getEquipment(ITEM_L2) ? 2 : 1)); //update to float i zwraca czas do odjêcia w zaleznosci czy drzwi zostaly uderzone czy nie
				
				
					if(bombState == TWO_BOMBS)
					{
						x1 = int(player->getBomb(1)->getX()-16)/32 - 1; //zamiana wspolrz na indexy mapy
						y1 = int(player->getBomb(1)->getY()-172)/32 - 1;
/*wybuch+zmiana czasu*/round->setTimeLeft(round->getTimeLeft() - round->getMap()->updateAfterExplosion(x1, y1, player->getEquipment(ITEM_L2) ? 2 : 1)); //update to float i zwraca czas do odjêcia w zaleznosci czy drzwi zostaly uderzone czy nie
					}
					bombState = player->detonateBomb();
					redraw = true;
				}
			}
		}
			
		if(redraw)// RYSOWANIE 
		{
			redraw = false;
			round->getMap()->draw(getRoundColor(round->getID()));	//mapa		
			
			if(bombState != NO_BOMB)//bomba
			{
				if(bombState == ONE_BOMB)
				{
					player->getBomb(0)->draw();
					
				}
				else if(bombState == TWO_BOMBS)
				{
					player->getBomb(0)->draw();
					player->getBomb(1)->draw();
				}
			}	
			
			player->draw(); //gracz
			
			for(int i = 0; i < MONSTER_COUNT; i++) //potwory
			{
				if(round->getMonster(i)->getIsActive() || round->getMonster(i)->getAnimDeathState()) round->getMonster(i)->draw();
			}
				
			camera->repair(); //...
			
			al_flip_display();	
		}

		if(player->getIsActive() == false && player->getAnimDeathState() == false) //jesli gracz niezyje i animacja rozpadu sie skonczyla
		{
			camera->update(-(camera->getMapScrollPx())); //reset kamery
			round->stopTheme();
			opt = GAME_OVER_SCREEN;
			exit();
		}

		if(isChallengeDone)//jesli gracz przeszedl gre
		{
			camera->update(-(camera->getMapScrollPx())); //reset kamery
			round->stopTheme();
			opt = COMPLETE_SCREEN;
			exit();
		}
	}
	
	return opt; 
}

void Challenge::checkField()
{
	int y = int(player->getY()-156); //-172 na interfejs i +16 na srodek pola
	int x = int(player->getX()); //-16 na interfejs i +16 na srodek pola

	ItemType itemField = round->getMap()->getField(x/32 -1, y/32 -1)->getItemType();

	if(round->getMap()->getField(x/32 -1, y/32 -1)->getFieldType() != SOFT_BRICK)
	{
		if(round->getMap()->getField(x/32 -1, y/32 -1)->getFieldType() == EXPLOSION)
		{
			player->die();				
		}	
		else if(itemField == DOOR) // drzwi
		{
			if(round->getMap()->getDoorState())//otwarte
			{
				//cout<<"drzwi otwarte"<<endl;
				roundDone();
				return;
			}
		}
		else if(itemField)//puste pole ma wartosc 0 wiec sie nie wywola
		{
			//cout<<"item zostal wziety"<<endl;
			round->setLevelItemState(true);
			isQuestDone = round->questDone(); //sprawdzenie czy cele rundy zostaly wykonane

			round->getMap()->getField(x/32 -1, y/32 -1)->setItemType(NO_ITEM);
		
			//dzwiek brania itemu:
			player->takeItemSound(round->getID());

			//dodanie itemu:
			player->setEquipment(round->getID(), true);

			//dodanie efektów:
			//czêœæ efektow mozna rozpoznac jedynie na podstawie getEquipment(id) (item 2,3 i 5) a te wymagaja osobnych warunków:

			if(round->getID() == 1) //wrotki lv1
			{
				player->setMovSpeed(2);
				if(int(player->getX())%2 != 0) player->setX(player->getX() - 1.0); //do kolizji. gracz ma teraz predkosc 2 wiec musi stac na parzystym px..
				if(int(player->getY())%2 != 0) player->setY(player->getY() - 1.0);
			}
	
			else if(round->getID() == 4) //przenikanie lv4
			{
				round->getMap()->makeFree();//wylacza kolizje z softbrickow. wyl kolizji z bomba jest gdzie indziej
			}
			
			//test w konsoli:
			for(int i=1;i<=5;i++)
			{
				cout<<player->getEquipment(i)<<" ";
			};cout<<endl;	
		}
	}	
}

void Challenge::roundDone()
{
	if(round->getID() != 5) //jeœli to runda od 1 do 4
	{
		points += round->getTimeLeft();
		
		clearNotUsed();
		al_stop_timer(controlTimer);
		
		round->stopTheme();
		al_reserve_samples(2);
		al_play_sample(getInstance()->resources->sample[S_ROUND_COMPLETE], 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_reserve_samples(1);
		al_rest(3.5);
		
		isQuestDone = false;
		round->setID(round->getID()+1);

		camera->update(-(camera->getMapScrollPx())); //reset kamery
		start();	
	}
	else //przejscie ost rundy
	{
		points += round->getTimeLeft();
		clearNotUsed();
		isChallengeDone = true;
	}
}

void Challenge::clearNotUsed()
{
	if(bombState != NO_BOMB) //reset bomb
	{
		round->getMap()->getField(int(player->getBomb(0)->getX()-16)/32 - 1, int(player->getBomb(0)->getY()-172)/32 - 1)->setIsFree(true);//pole gdzie by³a bomba0 jest teraz wolne;
		if(bombState == TWO_BOMBS)
		{
			round->getMap()->getField(int(player->getBomb(1)->getX()-16)/32 - 1, int(player->getBomb(1)->getY()-172)/32 - 1)->setIsFree(true);//pole gdzie by³a bomba1 jest teraz wolne;
		}
	}
}

float Challenge::getPoints() const
{
	return points;
}

