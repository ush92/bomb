#include "Map.h"

using namespace gameTypes;
using namespace std;

Map::Map(int X, int Y) //tworzy losow¹ mapê jako tablicê typu int
{
	map_X = X;
	map_Y = Y; 
	dens = 2;

	animStep = -1;
	animStep2 = -1;
	
	roundMap = new Field*[map_Y];//dlugosc
    for(int i=0; i<map_Y; i++)
        roundMap[i]=new Field[map_X]; //wysokosc

	isBurning = false;
}

Map::~Map(void)
{
    for(int i=0; i<map_Y; i++)
        delete[] roundMap[i];
 
	delete[] roundMap;
}

void Map::generateNewMap(ItemType roundItem, int dens)
{
	this->dens = dens;
	for(int i=0;i<map_Y;i++) //reset mapy
	{
		for(int j=0;j<map_X;j++)
		{
			roundMap[i][j].setFieldType(BLANK);
			roundMap[i][j].setItemType(NO_ITEM);
			roundMap[i][j].setIsFree(true);
		}
	}
	
	for(int i=0;i<map_Y;i++)  //losowanie
	{
		for(int j=0;j<map_X;j++)
		{
			if(i%2 == 1 && j%2 == 1) //co drugie pole jest nierozwalalny murek
			{
				roundMap[i][j].setFieldType(HARD_BRICK);
				roundMap[i][j].setIsFree(false);
			}
			else
			{
				if(i>2 || j>2) //zabezpieczenie przed zamurowaniem kilku poczatkowych pol zeby nie bylo smutnej sytuacji
				{
					//softbriki
					roundMap[i][j].setIsFree(rand() % dens == 0); //isFree jest prawd¹ dla liczb wiekszych od 0. dla 0 jest puste pole
					if(roundMap[i][j].getIsFree()) roundMap[i][j].setFieldType(BLANK);
					else roundMap[i][j].setFieldType(SOFT_BRICK);
				}
			}
		}
	}
	
	setItemPosition(roundItem);
	setItemPosition(DOOR);
	setDoorState(false);//drzwi s¹ zamkniête
}

void Map::draw(ALLEGRO_COLOR roundMapColor)
{
	for(int i=0;i<map_Y;i++)
	{
		for(int j=0;j<map_X;j++) 
		{
			switch(roundMap[i][j].getFieldType())	// 0-puste, 1-hardbrick, 2 softbrick
			{
				case BLANK:
					if(roundMap[i][j].getItemType() == NO_ITEM)
					{
						al_draw_filled_rectangle(48+j*32, 204+i*32, 80+j*32, 236+i*32, roundMapColor); //puste pole
						al_draw_bitmap(getInstance()->resources->bitmap[B_BLANK], 48+j*32, 204+i*32, NULL);
					}
					else if(roundMap[i][j].getItemType() == DOOR)
					{
						if(doorState)al_draw_bitmap(getInstance()->resources->bitmap[B_DOOR_O], 48+j*32, 204+i*32, NULL);
						else al_draw_bitmap(getInstance()->resources->bitmap[B_DOOR_C], 48+j*32, 204+i*32, NULL);
					}
					else if(roundMap[i][j].getItemType() == ITEM_L1)
					{
						al_draw_bitmap(getInstance()->resources->bitmap[B_ITEM1], 48+j*32, 204+i*32, NULL);
					}
					else if(roundMap[i][j].getItemType() == ITEM_L2)
					{
						al_draw_bitmap(getInstance()->resources->bitmap[B_ITEM2], 48+j*32, 204+i*32, NULL);
					}
					else if(roundMap[i][j].getItemType() == ITEM_L3)
					{
						al_draw_bitmap(getInstance()->resources->bitmap[B_ITEM3], 48+j*32, 204+i*32, NULL);
					}
					else if(roundMap[i][j].getItemType() == ITEM_L4)
					{
						al_draw_bitmap(getInstance()->resources->bitmap[B_ITEM4], 48+j*32, 204+i*32, NULL);
					}
					else if(roundMap[i][j].getItemType() == ITEM_L5)
					{
						al_draw_bitmap(getInstance()->resources->bitmap[B_ITEM5], 48+j*32, 204+i*32, NULL);
					}
					
					break;

				case HARD_BRICK:
					al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 48+j*32, 204+i*32, NULL);  //twardy murek
					break;
					
				case SOFT_BRICK:
					al_draw_bitmap(getInstance()->resources->bitmap[B_SOFT_BRICK], 48+j*32, 204+i*32, NULL);  //miêkki murek
					break;
				
				case EXPLODED_BRICK:
					burningBrickAnimation(i, j);
					break;
				case EXPLOSION:
					explosionAnimation(i, j);
			}
		}
	}
}

Field* Map::getField(int x, int y)
{
	return &roundMap[y][x];
}

void Map::setItemPosition(ItemType itemType)
{
	int i,j;
	bool done = false;
	while(!done)
	{
		i=rand() % (MAP_Y-3)+3;
		j=rand() % (MAP_X-3)+3; //te -3 +3 robi¹ ¿e indexy zaczynaj¹ siê od 3 a koñcz¹ normalnie na maxie macierzy
		if(roundMap[i][j].getFieldType() == SOFT_BRICK && roundMap[i][j].getItemType() == NO_ITEM)
		{		
			done = true;		
		}
	}
	cout<<"item "<<itemType<<": "<<i<<" "<<j<<endl;
	roundMap[i][j].setItemType(itemType);
}

void Map::setDoorState(bool state)
{
	doorState = state;
}

bool Map::getDoorState() const
{
	return doorState;
}

void Map::openDoor()
{
	for(int i=0;i<map_Y;i++)
	{
		for(int j=0;j<map_X;j++)
		{
			if(roundMap[i][j].getItemType() == DOOR)
			{
				if(roundMap[i][j].getFieldType() == BLANK) roundMap[i][j].setIsFree(true);//usun kolizje z drzwi jesli nie ma na nich murka
				setDoorState(true); // otworz drzwi
			}
		}
	}
}

void Map::makeFree()
{
	for(int i=0;i<map_Y;i++)
	{
		for(int j=0;j<map_X;j++) 
		{
			if(roundMap[i][j].getItemType() != DOOR && roundMap[i][j].getFieldType() == SOFT_BRICK)
			{
				roundMap[i][j].setIsFree(true);
			}
		}
	}
}

void Map::burningBrickAnimation(int y, int x)
{
	isBurning = true;
	++animStep %= 8;
	if(animStep<7)
	{
		al_draw_bitmap_region(getInstance()->resources->bitmap[B_SOFT_BRICK_BURN], 32 * (animStep), 0, 32, 32, x*32 + 48, y*32 + 204, NULL);
	}
	else if(animStep==7)
	{
		roundMap[y][x].setFieldType(BLANK);
		animStep = -1;
		isBurning = false;
	}
}

void Map::explosionAnimation(int y, int x)
{
	isBurning = true;
	++animStep2 %= 8;
	if(animStep2<7)
	{
		al_draw_bitmap_region(getInstance()->resources->bitmap[B_EXPLOSION], 32 * (animStep2), 0, 32, 32, x*32 + 48, y*32 + 204, NULL);
	}
	else if(animStep2==7)
	{
		roundMap[y][x].setFieldType(BLANK);
		animStep2 = -1;
		isBurning = false;
	}
}

bool Map::getisBurning() const
{
	return isBurning;
}

float Map::updateAfterExplosion(int bombx, int bomby, int explosionRange)//usuwa murki wokol bomby i zwraca karê czasu jesli bomba uderzy³a w drzwi
{
	bool destroyMore;//zmienna pomocnicza. zatrzymuje niszczenie murkow gdy wybuch natrafi na soft brick
	int doorDamagedPenalty = 0;
	int i; //licznik pomocniczy do pêtli
		
	if(getField(bombx,bomby)->getFieldType() != SOFT_BRICK) //jesli pole gdzie postawiona byla bomba nie jest S_BRICKIEM to..
	{
		getField(bombx,bomby)->setIsFree(true);//srodek, tjpole na ktorym stala bomba jest teraz wolne. nie bedzie to softbrick bo warunek wyzej to uniemozliwia
		
		for(int dir = 1; dir<=4; dir++) //pozosta³e 4 strony
		{
			i = 1; 
			destroyMore = true;

			getField(bombx,bomby)->setFieldType(EXPLOSION);//pole z bomb¹ oczywiscie tez wybucha..

			if(dir == 1) //LEWA STRONA 
			{
				while(i<=explosionRange)
				{
					if(bombx - i >= 0) //jezeli wybuch nie wychodzi za mape 
					{
						if(getField(bombx-i,bomby)->getFieldType() == HARD_BRICK) //jezeli pole to hard murek 
						{ 
							destroyMore = false; //to nie niszcz niczego z tej strony
						}
						else if (getField(bombx-i,bomby)->getItemType() == DOOR && //pole to drzwi (i na drzwiach nie ma juz murka!!!)
								 getField(bombx-i,bomby)->getFieldType() == BLANK && destroyMore)
						{
							destroyMore = false;
							damageDoor();
							doorDamagedPenalty = 30;
						}		
						else if(getField(bombx-i,bomby)->getFieldType() == SOFT_BRICK && destroyMore) //jezeli strona ma byæ jednak niszczona i pole to soft brick to
						{
							destroyBrick(bombx-i,bomby); //zniszcz pole
							destroyMore = false;//1 murek zostal zniszczony wiec nie rozwalaj juz wiecej z tej strony
						}
						else if(getField(bombx-i,bomby)->getItemType() == NO_ITEM &&//jesli na polu nie ma niczego (murka,drzwi itemu)
							getField(bombx-i,bomby)->getFieldType() == BLANK && destroyMore)
						{
							getField(bombx-i,bomby)->setFieldType(EXPLOSION);
						}
					}
					i++; //zwiêksz promieñ wybuchu
				}
			}
			else if(dir == 2) //PRAWA STRONA
			{
				while(i<=explosionRange)
				{
					if(bombx + i <= MAP_X-1)
					{
						if(getField(bombx+i,bomby)->getFieldType() == HARD_BRICK) //jezeli pole to hard murek 
						{ 
							destroyMore = false; //to nie niszcz niczego z tej strony
						}
						else if (getField(bombx+i,bomby)->getItemType() == DOOR && //pole to drzwi (i na drzwiach nie ma juz murka!!!)
								 getField(bombx+i,bomby)->getFieldType() == BLANK && destroyMore)
						{
							destroyMore = false;
							damageDoor();
							doorDamagedPenalty = 30;
						}		
						else if(getField(bombx+i,bomby)->getFieldType() == SOFT_BRICK && destroyMore) //jezeli strona ma byæ jednak niszczona i pole to soft brick to
						{
							destroyBrick(bombx+i,bomby); //zniszcz pole
							destroyMore = false;//1 murek zostal zniszczony wiec nie rozwalaj juz wiecej z tej strony
						}
						else if(getField(bombx+i,bomby)->getItemType() == NO_ITEM &&//jesli na polu nie ma niczego (murka,drzwi itemu)
							getField(bombx+i,bomby)->getFieldType() == BLANK && destroyMore)
						{
							getField(bombx+i,bomby)->setFieldType(EXPLOSION);
						}
					}
					i++;
				}
			}
			else if(dir == 3) //DOL
			{
				while(i<=explosionRange)
				{
					if(bomby + i <= MAP_Y-1)
					{
						if(getField(bombx,bomby+i)->getFieldType() == HARD_BRICK) //jezeli pole to hard murek 
						{ 
							destroyMore = false; //to nie niszcz niczego z tej strony
						}
						else if (getField(bombx,bomby+i)->getItemType() == DOOR && //pole to drzwi (i na drzwiach nie ma juz murka!!!)
								 getField(bombx,bomby+i)->getFieldType() == BLANK && destroyMore)
						{
							destroyMore = false;
							damageDoor();
							doorDamagedPenalty = 30;
						}		
						else if(getField(bombx,bomby+i)->getFieldType() == SOFT_BRICK && destroyMore) //jezeli strona ma byæ jednak niszczona i pole to soft brick to
						{
							destroyBrick(bombx,bomby+i); //zniszcz pole
							destroyMore = false;//1 murek zostal zniszczony wiec nie rozwalaj juz wiecej z tej strony
						}
						else if(getField(bombx,bomby+i)->getItemType() == NO_ITEM &&//jesli na polu nie ma niczego (murka,drzwi itemu)
							getField(bombx,bomby+i)->getFieldType() == BLANK && destroyMore)
						{
							getField(bombx,bomby+i)->setFieldType(EXPLOSION);
						}
					}
					i++;
				}
			}
			else if(dir == 4) //GORA 
			{
				while(i<=explosionRange)
				{
					if(bomby - i >= 0) 
					{
						if(getField(bombx,bomby-i)->getFieldType() == HARD_BRICK) //jezeli pole to hard murek 
						{ 
							destroyMore = false; //to nie niszcz niczego z tej strony
						}
						else if (getField(bombx,bomby-i)->getItemType() == DOOR && //pole to drzwi (i na drzwiach nie ma juz murka!!!)
								 getField(bombx,bomby-i)->getFieldType() == BLANK && destroyMore)
						{
							destroyMore = false;
							damageDoor();
							doorDamagedPenalty = 30;
						}		
						else if(getField(bombx,bomby-i)->getFieldType() == SOFT_BRICK && destroyMore) //jezeli strona ma byæ jednak niszczona i pole to soft brick to
						{
							destroyBrick(bombx,bomby-i); //zniszcz pole
							destroyMore = false;//1 murek zostal zniszczony wiec nie rozwalaj juz wiecej z tej strony
						}
						else if(getField(bombx,bomby-i)->getItemType() == NO_ITEM &&//jesli na polu nie ma niczego (murka,drzwi itemu)
							getField(bombx,bomby-i)->getFieldType() == BLANK && destroyMore)
						{
							getField(bombx,bomby-i)->setFieldType(EXPLOSION);
						}
					}
					i++;
				}
			}
		}
	}
	return doorDamagedPenalty;
}

void Map::damageDoor()
{
	al_reserve_samples(2);
	al_play_sample(getInstance()->resources->sample[S_BAD_TIME], 1.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	al_play_sample(getInstance()->resources->sample[S_BAD_TIME], 1.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	al_reserve_samples(1);
}

void Map::destroyBrick(int dirx, int diry) 
{
	getField(dirx, diry)->setFieldType(EXPLODED_BRICK);//ustaw na pole które sie pali
	if(getField(dirx, diry)->getItemType() != DOOR)//jesli pole to nie drzwi, czyli np item...
	{
		getField(dirx, diry)->setIsFree(true);	//...to usun kolizjê

	}
	else //...a jesli to drzwi...
	{
		if(getDoorState()) //..to jesli drzwi sa otwarte...
		{
			getField(dirx, diry)->setIsFree(true);	//...to usun kolizjê
		}
	}
}