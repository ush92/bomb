#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(void)
{
	bomb[0] = new Bomb();
	bomb[1] = new Bomb();
	for(int i=0;i<5;i++)
	{
		equipment[i] = true;
	}
	reset();
}

Player::~Player(void)
{
	delete bomb[0];
	delete bomb[1];
}

void Player::draw()//dir przyjmuje wartosci od 0 do 3. 32*dir oznacza wspolrzedne y spritesheetu
{                                         //step od 0 do 2. dzielenie do normalizacji klatek. patrz character.animate()
	if(isActive) al_draw_bitmap_region(getInstance()->resources->bitmap[B_PLAYER], 32*(animStep/4), 32*animDir, 32, 32, x, y, NULL);
	else
	{
		if(anim_death)
		{
			al_draw_bitmap_region(getInstance()->resources->bitmap[B_PLAYER_DEATH], 32*(animStep/5), 0, 32, 32, x, y, NULL);
			++animStep %= 7*5;//7 klatek spowolnionych 5ciokrotnie
		}

		if (animStep == 34)
		{
			anim_death = false;
		}
	}
}

void Player::reset()
{
	isActive = true;//gracz zyje
	x = 48;	//poczatkowy x
	y = 204; //... oraz y
	
	animStep = 0;//0,1 lub 2
	animDir = DOWN;

	bomb[0]->setIsActive(false);
	bomb[1]->setIsActive(false);

	if(getEquipment(ITEM_L1)) setMovSpeed(2);
	else setMovSpeed(1);

	ghostCollision = false; //brak przenikania przez sciany bez itemu nr 5

	anim_death = true; //animacja smierci moze zostac wykonana
}

BombState Player::putBomb(float x, float y)
{
	if(int(x-16) % 32 != 0) //wyrównanie bomby tak zeby sta³a na okreslonym polu, a nie gdzies miedzy polami
	{
		if(int(x-16) % 32 < 15) //15px tolerancji
		{
			x = x - (int(x-16) % 32);//stawienie na polu polu po lewej
		}
		else
		{
			x = x - (int(x-16) % 32) + 32;//..po prawej
		}
	}
	
	if(int(y-172) % 32 != 0) 
	{
		if(int(x-172) % 32 > 15)//15 to 15px tolerancji
		{
			y = y - (int(y-172) % 32);//stawienie na polu polu na gorze
		}
		else
		{
			y = y - (int(y-172) % 32) + 32;//..na dole
		}
	}

	if(bomb[0]->getIsActive() && bomb[1]->getIsActive() && getEquipment(ITEM_L5)) //dwie bomby sa podlozone
	{
		cout<<"pusty magazynek 0/2"<<endl;
		bomb[0]->errSound(); //dzwiek bledu stawiania bomby
		return TWO_BOMBS;
	}
	else if (bomb[0]->getIsActive() && !getEquipment(ITEM_L5))
	{
		cout<<"pusty magazynek 0/1"<<endl;
		bomb[0]->errSound(); //dzwiek bledu stawiania bomby
		return ONE_BOMB;
	}
	else 
	{
		if(bomb[0]->getIsActive() == false)
		{
			bomb[0]->setIsActive(true);
			bomb[0]->setX(x);
			bomb[0]->setY(y);
			
			bomb[0]->putSound(getEquipment(ITEM_L3)); //dzwiek zalezny od posiadania detonatora
			
			return ONE_BOMB;
		}
		else if(bomb[1]->getIsActive() == false)
		{
			if(x!=bomb[0]->getX() || y!=bomb[0]->getY()) //jezeli wspolrzedne pierwszej bomby sa takie jak nowej..
			{
				bomb[1]->setIsActive(true);
				bomb[1]->setX(x);
				bomb[1]->setY(y);
				
				bomb[1]->putSound(getEquipment(ITEM_L3)); //dzwiek zalezny od posiadania detonatora i jeszcze - 2 bo indexy
				
				return TWO_BOMBS;
			}
			else
			{
				bomb[1]->errSound();
				cout<<"bomby nie moga na sobie lezec"<<endl;
				return ONE_BOMB;
			}
		}
	}

	al_show_native_message_box(NULL, "Game", "Error", "Program wykonal nieprawidlowa operacje \nplayerPutBomb()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	return NO_BOMB;
}

BombState Player::detonateBomb()
{
	if(bomb[0]->getIsActive() || bomb[1]->getIsActive())
	{
		bomb[0]->boomSound();//obojetnie ktora bomba wyda dzwiek
	}

	bomb[0]->setIsActive(false);
	bomb[1]->setIsActive(false);
	return NO_BOMB;
}

Bomb* Player::getBomb(int id) const
{
	return bomb[id];
}

void Player::moveUDSound() const
{
	al_play_sample(getInstance()->resources->sample[S_MOVE_UD], 0.7, 0.0, getMovSpeed()/2, ALLEGRO_PLAYMODE_ONCE, 0);
}

void Player::moveLRSound() const
{
	al_play_sample(getInstance()->resources->sample[S_MOVE_LR], 0.6, 0.0, getMovSpeed()/2, ALLEGRO_PLAYMODE_ONCE, 0);
}

bool Player::getEquipment(int id) const
{
	return equipment[id-1];
}

void Player::setEquipment(int id, bool isTaken)
{
	equipment[id-1] = isTaken;
}

void Player::takeItemSound(int id) const
{
	al_reserve_samples(2);
	al_play_sample(getInstance()->resources->sample[14+id], 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	al_reserve_samples(1);
}

void Player::die()
{
	if(isActive) //dzwiek i zresetowanie animacji. ten fragment kodu wykona sie tylko raz po smierci gracza
	{
		al_stop_samples();
		al_reserve_samples(2);
		al_play_sample(getInstance()->resources->sample[S_BAD_TIME], 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_play_sample(getInstance()->resources->sample[S_U_DIE], 1.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_reserve_samples(1);
		
		animStep=0;	
	}
	isActive = false;
}

bool Player::getAnimDeathState()
{
	return anim_death;
}

