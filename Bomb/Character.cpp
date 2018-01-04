#include "Character.h"

Character::Character(void)
{
	
}

Character::~Character(void)
{
}

void Character::movDown()
{
	y+=movSpeed;
}

void Character::movUp()
{
	y-=movSpeed;
}

void Character::movRight()
{
	x+=movSpeed;
}

void Character::movLeft()
{
	x-=movSpeed;
}

float Character::getX() const
{
	return x;
}

float Character::getY() const
{
	return y;
}

void Character::setX(float x)
{
	this->x = x;
}

void Character::setY(float y)
{
	this->y = y;
}

void Character::setIsActive(bool isActive)
{
	this->isActive = isActive;
}

bool Character::getIsActive() const
{
	return isActive;
}

void Character::setAnimStep(int step)
{
	animStep = step;
}

void Character::setAnimDir(Direction dir)
{
	animDir = dir;
}

Direction Character::getAnimDir() const
{
	return animDir;
}

void Character::animate()
{
	++animStep %= 12;
}

float Character::getMovSpeed() const
{
	return movSpeed;
}

void Character::setMovSpeed(float movSpeed)
{
	this->movSpeed = movSpeed;
}

bool Character::detectCollision(Direction direction, Map* map)//-1 pole z postacia, 0 pole w prawo/dol, -2 w gore/lewo
{
	int yy = int(getY()-172);
	int xx = int(getX()-16);
	
	switch(direction)
	{
		case UP:
			if(getY() <= MAP_UP)
			{
				setY(MAP_UP);
				return false;
			}
			else if(yy % 32 == 0) //jezeli gracz stoi na krawedzi y...
			{					
				if(xx % 32 == 0) //jezeli gracz stoi na krawedzi x to sprawdz 1 pole na gorze...
				{
					if(!(map->getField(xx/32-1, yy/32-2)->getIsFree())) //jezeli pole nie jest wolne
					{
						if(ghostCollision == true)
						{
							if(map->getField(xx/32-1, yy/32-2)->getFieldType() == HARD_BRICK) return false;	
							else return true;
						} 
						else return false;
					}
				}//w przeciwnym wypadku sprawdz 2 pola na gorze i wykryj kolizje gdy jedno z nich jest zajête
				else 
				{
					if(!(map->getField(xx/32-1, yy/32-2)->getIsFree()) //tu nie musze sprawdzac warunku na ghostCollision bo ona dotyczy tylko potwórów, a one nie chodz¹ "krzywo". dla gracza jest metoda makeFree w klasie map
					 || !(map->getField(xx/32, yy/32-2)->getIsFree()))
					{
						return false;
					}
				}
			}
			break;

		case DOWN:
			if(getY() >= MAP_DOWN)
			{
				setY(MAP_DOWN);
				return false;
			}
			else if(yy % 32 == 0) //jezeli gracz stoi na krawedzi Y to...
			{					
				if(xx % 32 == 0) //jezeli gracz stoi na krawedzi X to sprawdz 1 pole na dole...
				{
					if(!(map->getField(xx/32-1, yy/32)->getIsFree()))
					{
						if(ghostCollision == true)
						{
							if(map->getField(xx/32-1, yy/32)->getFieldType() == HARD_BRICK) return false;	
							else return true;
						} 
						else return false;
					}
				}//w przeciwnym wypadku sprawdz 2 pola na dole i wykryj kolizje gdy jedno z nich jest zajête
				else 
				{
					if(!map->getField(xx/32-1, yy/32)->getIsFree()
					 || !(map->getField(xx/32, yy/32)->getIsFree()))
					{
						return false;
					}
				}
			}
			break;

		case LEFT:
			if(getX() <= MAP_LEFT)
			{
				setX(MAP_LEFT);
				return false;
			}
			else if(xx % 32 == 0) //jezeli gracz stoi na krawedzi X to...
			{					
				if(yy % 32 == 0) //jezeli gracz stoi na krawedzi Y to sprawdz 1 pole na lewo...
				{
					if(!(map->getField(xx/32-2, yy/32-1)->getIsFree()))
					{
						if(ghostCollision == true)
						{
							if(map->getField(xx/32-2, yy/32-1)->getFieldType() == HARD_BRICK) return false;	
							else return true;
						} 
						else return false;
					}
				}//w przeciwnym wypadku sprawdz 2 pola po lewej i wykryj kolizje gdy jedno z nich jest zajête
				else 
				{
					if(!(map->getField(xx/32-2, yy/32-1)->getIsFree())
					 || !(map->getField(xx/32-2, yy/32)->getIsFree()))
					{
						return false;
					}
				}
			}
			break;

		case RIGHT:
			if(getX() >= MAP_RIGHT)
			{
				setX(MAP_RIGHT);
				return false;
			}
			else if(xx % 32 == 0) //jezeli gracz stoi na krawedzi X to...
			{					
				if(yy % 32 == 0) //jezeli gracz stoi na krawedzi Y to sprawdz 1 pole w prawo...
				{
					if(!(map->getField(xx/32, yy/32-1)->getIsFree()))
					{
						if(ghostCollision == true)
						{
							if(map->getField(xx/32, yy/32-1)->getFieldType() == HARD_BRICK) return false;	
							else return true;
						} 
						else return false;
					}
				}//w przeciwnym wypadku sprawdz 2 pola po prawej i wykryj kolizje gdy jedno z nich jest zajête
				else 
				{
					if(!(map->getField(xx/32, yy/32-1)->getIsFree())
					 || !(map->getField(xx/32, yy/32)->getIsFree()))
					{
						return false;
					}
				}
			}
			break;
	}
	return true;//jesli kolizja niewystêpuje
}

void Character::setAnimDeathState(bool state)
{
	anim_death = state;
}

bool Character::getAnimDeathState() const
{
	return anim_death;
}
