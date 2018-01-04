#include "Bomb.h"


Bomb::Bomb(void)
{
	isActive = false;
	animStep=0;
	x=0;
	y=0;
}


Bomb::~Bomb(void)
{
}

bool Bomb::getIsActive() const
{
	return isActive;
}

void Bomb::setIsActive(bool active)
{
	isActive = active;
	lifeTime = 0;
}

void Bomb::animate()
{
	++animStep %= 15; //jak tu jest mod 3 to w draw dzieli sie przez 1. im wieksza wartosc tym wolniejsza animacja
}

void Bomb::draw()
{
	al_draw_bitmap_region(getInstance()->resources->bitmap[B_BOMB], 32 * (animStep/5), 0, 32, 32, x, y, NULL);
}

void Bomb::setX(float x)
{
	this->x = x;
}

void Bomb::setY(float y)
{
	this->y = y;
}

float Bomb::getX() const
{
	return x;
}

float Bomb::getY() const
{
	return y;
}

bool Bomb::selfExplode()
{
	lifeTime += 0.017;

	if(lifeTime > 2.6)
	{
		lifeTime = 0;
		return true;
	}
	
	return false;
}

void Bomb::putSound(bool detonator) const //dzwiek stawiania bomby zalezny od posiadania detoantora
{
	if(detonator)
	{ 
		al_reserve_samples(2);
		if(rand()%2) al_play_sample(getInstance()->resources->sample[S_PUT_BOMB_OK_DET], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		else al_play_sample(getInstance()->resources->sample[S_PUT_BOMB_OK_DET2], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_reserve_samples(1);
	}
	else
	{
		al_reserve_samples(2);
		al_play_sample(getInstance()->resources->sample[S_PUT_BOMB_OK], 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_reserve_samples(1);
	}
}


void Bomb::errSound() const
{
	al_reserve_samples(2);
	al_play_sample(getInstance()->resources->sample[S_PUT_BOMB_ERR], 1.5, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	al_reserve_samples(1);
}

void Bomb::boomSound() const
{
	al_stop_samples();
	switch(rand()%3) //losowa melodyjka explozji 
	{
		case 0:
			al_play_sample(getInstance()->resources->sample[S_BOOM1], 0.8, 0.0, 0.8, ALLEGRO_PLAYMODE_ONCE, 0);
			break;
		
		case 1:
			al_play_sample(getInstance()->resources->sample[S_BOOM2],0.8, 0.0, 0.8, ALLEGRO_PLAYMODE_ONCE, 0);
			break;
		
		case 2:
			al_play_sample(getInstance()->resources->sample[S_BOOM3], 0.8, 0.0, 0.8, ALLEGRO_PLAYMODE_ONCE, 0);
			break;
	}
}
