#pragma once
#include "character.h"
#include "Bomb.h"

class Player :
	public Character
{
public:
	Player(void);
	~Player(void);
	void draw();
	void reset();
	BombState putBomb(float x, float y);
	BombState detonateBomb();
	Bomb* getBomb(int id) const;
	void moveUDSound() const;
	void moveLRSound() const;
	void takeItemSound(int id) const;
	bool getEquipment(int id) const;
	void setEquipment(int id, bool isTaken);
	void die();
	bool getAnimDeathState();
private:
	bool isPlayer;
	array <bool, 5> equipment;
	Bomb* bomb[2];
};

