#include "Monster.h"

Monster::Monster(void)
{
	animDir = DOWN;
	animStep = 0;
}

Monster::~Monster(void)
{
}

void Monster::draw()
{                                         //step od 0 do 2. a dzielenie w step do normalizacji klatek. patrz character.animate()
	if(isActive)
	{
		if(type != BOSS)
		{
			if(animDir == RIGHT)
			{
				al_draw_bitmap_region(getInstance()->resources->bitmap[bitmap],32*(animStep/4), 0, 32, 32, x, y, ALLEGRO_FLIP_HORIZONTAL);
			}
			else al_draw_bitmap_region(getInstance()->resources->bitmap[bitmap],32*(animStep/4), 0, 32, 32, x, y, NULL);
		}
		else al_draw_bitmap_region(getInstance()->resources->bitmap[B_BOSS], 32*(animStep/4), 32*animDir, 32, 32, x, y, NULL);
	}
	else
	{
		if(anim_death)
		{
			if(type != BOSS) 
			{
				al_draw_bitmap_region(getInstance()->resources->bitmap[bitmap], 96, 0, 32, 32, x, y, NULL);
			}
			else
			{
				al_draw_bitmap_region(getInstance()->resources->bitmap[B_PLAYER_DEATH], 32*(animStep/5), 0, 32, 32, x, y, NULL);
			}
			++animStep %= 7*5;//7 klatek spowolnionych 5ciokrotnie
		}

		if (animStep == 34)
		{
			anim_death = false;
		}
	}
}

void Monster::setType(MonsterType type)
{
	this->type = type; //do nadania potworowi odpowiednich cech 
	
	switch(type)
	{
		case JELLY:
			bitmap = B_JELLY;
			setMovSpeed(1);
			maxStep = 20*32;
			healthPoints = 1;
			ghostCollision = false;
			break;

		case TOXIN:
			bitmap = B_TOXIN;
			setMovSpeed(2);
			maxStep = 9*32; 
			healthPoints = 1;
			ghostCollision = false;
			break;

		case BAD_BRICK:
			bitmap = B_BAD_BRICK;
			setMovSpeed(4);
			maxStep = 0; //nigdy nie zmienia kierunku bez kolizji, dodac warunek nizej
			healthPoints = 1;
			ghostCollision = false;
			break;
	
		case GHOST:
			bitmap = B_GHOST;
			setMovSpeed(2);
			maxStep = 10*32; 
			healthPoints = 1000000;//wzglêdna niesmiertelnosc
			ghostCollision = true;
			break;

		case BOSS:
			bitmap = B_BOSS;
			setMovSpeed(2);
			maxStep = 28*32;
			healthPoints = 150; 
			ghostCollision = true;
			break;
	}

	step = maxStep;//w ten sposob metoda control wylosuje kierunek i zresetuje liczbe krokow
}

void Monster::control(Map* map, Player* player)
{
	if(isActive)
	{
		if(type<BOSS)
		{
			if(detectCollision(animDir, map))
			{
				if(step >= maxStep && type != BAD_BRICK)
				{
					step = 0;
					changeDirection();
				}
				else
				{
					switch(animDir)
					{
						case UP:
							setY(y - movSpeed);
							break;

						case DOWN:
							setY(y + movSpeed);
							break;

						case RIGHT:
							setX(x + movSpeed);
							break;

						case LEFT:
							setX(x - movSpeed);
							break;
					}
					step += movSpeed;
					animate();
				}
			}
			else changeDirection();
		}

		else //ruch bossa czyli szukanie naszej postaci
		{
			if(detectCollision(animDir, map))
			{
			
				if(step)//zmiana na normalna predkosc
				{
					setMovSpeed(2);
				}
			
				if(step >= maxStep)
				{
					changeDirection2(player);
				}
			
				switch(animDir)
				{
					case UP:
						setY(y - movSpeed);
						break;

					case DOWN:
						setY(y + movSpeed);
						break;

					case RIGHT:
						setX(x + movSpeed);
						break;

					case LEFT:
						setX(x - movSpeed);
						break; 
				}
			
				animate();
				step += movSpeed;
			
				if (player->getX() == this->getX() && player->getY() < this->getY()) 
				{
					animDir = UP;
					setMovSpeed(4);
					step = 0;
				}
				else if (player->getX() == this->getX() && player->getY() > this->getY())
				{
					animDir = DOWN;
					setMovSpeed(4);
					step = 0;
				}
				else if (player->getY() == this->getY() && player->getX() < this->getX())
				{
					animDir = LEFT;
					setMovSpeed(4);
					step = 0;
				}
				else if (player->getY() == this->getY() && player->getX() > this->getX()) 
				{
					animDir = RIGHT;
					setMovSpeed(4);
					step = 0;
				}
			}
			else
			{
				changeDirection2(player);
			}
		}

		if(map->getField(x/32 -1, (y-156)/32 -1)->getFieldType() == EXPLOSION) //x+16-16, y-176+16 //patrz challange.checkField
		{
			if(type == BOSS)
			{
				al_reserve_samples(2);
				al_play_sample(getInstance()->resources->sample[S_DMG_BOSS], 1.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				al_reserve_samples(1);
				
			}
			healthPoints--;
			if(!healthPoints) die();
		}	
	}
}

void Monster::changeDirection()
{
	switch(rand()%4) //kierunki od 0 do 3 
	{
		case 0:
			if(animDir == DOWN) animDir = UP;
			else animDir = DOWN;
			break;
		
		case 1:
			if(animDir == UP) animDir = DOWN;
			else animDir = UP;
			break;

		case 2:
			if(animDir == LEFT) animDir = RIGHT;
			else animDir = LEFT;
			break;
		
		case 3:
			if(animDir == RIGHT) animDir = LEFT;
			else animDir = RIGHT;
			break;
	}	
}

void Monster::changeDirection2(Player* pl)
{
	bool change = true;
	step = 0;
	setMovSpeed(2);
	if((animDir == LEFT || animDir == RIGHT) && change)
	{
		if(pl->getY() < this->getY())
		{
			animDir = UP;
		}
		else
		{
			animDir = DOWN;
		}
		change = false;
	}
			
	if((animDir == UP || animDir == DOWN) && change)
	{
		if(pl->getX() < this->getX())
		{
			animDir = LEFT;
		}
		else
		{
			animDir = RIGHT;
		}
		change = false;
	}
}

bool Monster::killPlayer(Player* player)
{	
	float m_x = getX() + 16;
	float m_y = getY() + 16;
	float p_x = player->getX() + 16;
	float p_y = player->getY() + 16;

	if( (fabs(p_x - m_x) < 32) && (fabs(p_y - m_y) < 32 ) && isActive ) //jesli bezwgledna odlegolosc do gracza jest mniejsza niz 1 pole i potwor zyje to
	{
		//cout<<fabs(p_x - m_x)<<" "<<fabs(p_y - m_y)<<endl;
		return true;//potwor nas zabi³
	}
	else
	{
		return false; //nic sie nie sta³o.
	}
}

int Monster::getHealthPoints() const
{
	return healthPoints;
}

void Monster::die()
{
	if(isActive) //dzwiek i zresetowanie animacji. ten fragment kodu wykona sie tylko raz po smierci potwora
	{
		al_stop_samples();
		al_reserve_samples(2);
		if(type != BOSS) al_play_sample(getInstance()->resources->sample[S_MON_DIE], 1.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		else al_play_sample(getInstance()->resources->sample[S_DEATH_BOSS], 1.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_reserve_samples(1);
		
		animStep=0;	
	}
	isActive = false;
}
