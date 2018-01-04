#include "Round.h"

Round::Round(void)
{
	map = new Map(MAP_X, MAP_Y);//wielkosc mapy i gêstoœæ losowania murków
	roundTheme = al_create_sample_instance(getInstance()->resources->sample[S_ROUND1]);
	lowTimeTheme = al_create_sample_instance(getInstance()->resources->sample[S_LOW_TIME]);
	loadingScreen = new RoundLoader();
	for(int i = 0; i<6; i++)
	{
		monster[i] = new Monster();
	}
}

Round::~Round(void)
{
	delete map;
	delete loadingScreen;
	al_destroy_sample_instance(roundTheme);
	al_destroy_sample_instance(lowTimeTheme);
	for(int i = 0; i<6; i++)
	{
		delete monster[i];
	}
}

void Round::playTheme()
{
	al_stop_sample_instance(lowTimeTheme);
	al_destroy_sample_instance(roundTheme);
	roundTheme = al_create_sample_instance(getInstance()->resources->sample[ID]);
	al_set_sample_instance_playmode(roundTheme, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(roundTheme, al_get_default_mixer());
	al_play_sample_instance(roundTheme);
}

void Round::createLowTimeEvent()
{
	if(!lowTimeEvent)
	{
		al_stop_sample_instance(roundTheme);
		lowTimeTheme = al_create_sample_instance(getInstance()->resources->sample[S_LOW_TIME]);
		al_set_sample_instance_playmode(lowTimeTheme, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(lowTimeTheme, al_get_default_mixer());
		al_play_sample_instance(lowTimeTheme);
		if(ID == 5) monster[0]->setMovSpeed(4);
		lowTimeEvent = true;
	}
}

Map* Round::getMap() const
{
	return map;
}

void Round::stopTheme()
{
	al_stop_sample_instance(roundTheme);
	al_stop_sample_instance(lowTimeTheme);
}

int Round::getID() const
{
	return ID;
}

Monster* Round::getMonster(int id) const
{
	return monster[id];
}

void Round::reset()
{
	levelItem = ItemType(ID);
	levelMonster = MonsterType(ID-1);
	cout<<ID<<endl;
	createName(ID); 
	map->generateNewMap(levelItem,ID<=3 ? 2 : 3); //tworzenie nowej mapki. parametr: item, oraz gêstoœæ murków zale¿ny od ID
	levelItemState = false;
	
	switch(ID)
	{
		case 1:
			timeLeft = 500;
			break;

		case 2:
			timeLeft = 450;
			break;

		case 3:
			timeLeft = 300;
			break;

		case 4:
			timeLeft = 225;
			break;

		case 5:
			timeLeft = 400;
			break;
	}
	lowTimeEvent = false;
	
	respawnMonsters();
	lastMonsterSound = true;

	loadingScreen->set(ID, name);
	loadingScreen->show();
	
	playTheme();

	if(ID == 5) map->makeFree(); //item z 4 rundy ma oczywiscie dzialac tez w 5tej.
}

void Round::setID(int id)
{
	ID = id;
}

void Round::setLevelItemState(bool levelItemState)
{
	this->levelItemState = levelItemState;
}

bool Round::getLevelItemState()
{
	return levelItemState;
}

void Round::setMonstersCount(int monstersCount)
{
	this->monstersCount = monstersCount;
}

int Round::getMonstersCount() const
{
	return monstersCount;
}

void Round::setActiveMonsters(int activeMonsters)
{
	this->activeMonsters = activeMonsters;
}

int Round::getActiveMonsters()
{	
	return activeMonsters;
}

void Round::setTimeLeft(float timeLeft)
{
	this->timeLeft = timeLeft;
}

float Round::getTimeLeft() const
{
	return timeLeft;
}

void Round::decrementTime()
{
	timeLeft -= 0.017;
}

void Round::createName(int id)
{
	switch(id)
	{
		case 1:
			name = "Jelly Facility";
			break;

		case 2:
			name = "Toxic Factory";
			break;
			
		case 3:
			name = "TNT Armory";
			break;
		
		case 4:
			name = "Desolation";
			break;

		case 5:
			name = "Event Horizon";
			break;
	}
}

string Round::getName() const
{
	return name;
}

bool Round::questDone() 
{
	activeMonsters = monstersCount;
	for(int i = 0; i<monstersCount; i++)
	{
		if(monster[i]->getIsActive() == false) activeMonsters--;
	}
	
	if(lastMonsterSound && !activeMonsters)
	{
		lastMonsterSound = false;
		al_reserve_samples(2);
		al_play_sample(getInstance()->resources->sample[S_LAST_MON], 1.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		al_reserve_samples(1);
	}

	//quest w rundach 1-3 i 5 to zabicie wrogów i wziecie itemu, w rundzie 4 trzeba tylko wzi¹c item
	if((!activeMonsters && levelItemState && ID != 4) || (levelItemState && ID == 4)) //jezeli nie ma potworow i item zostal wziety
	{
		//cout<<"DRZWI ZOSTALY OTWARTE!!"<<endl;
		map->openDoor();
		return true;
	}
	else return false;
}

void Round::respawnMonsters()
{
	if (ID<=4)
	{
		monstersCount = 6; 
		activeMonsters = 6;
	}
	else
	{
		monstersCount = 1; //w ost rundzie jest 1 boss 
		activeMonsters = 1;
	}

	if(ID==5)
	{
		for(int i = 0; i < 6; i++) //zabija duchy bo gracz sam tego nie zrobi :c
		{	
			monster[i]->setAnimDeathState(false);	
			monster[i]->setIsActive(false);		
		}
	}

	int i=0; 
	int m_x, m_y;//wspolrzedne macierzy mapy (losowane)
	float r_x, r_y;//realne wspolrzedne w px
	while(i<monstersCount)
	{
		if(ID<=3)//w rundach 1-3 potwory moga respic sie bardziej na poczatku. w 4 i 5 niebardzo xD
		{
			m_y = rand()%6 +5; // w ten sposob potwory nie respia sie na polach mniejszych od 5 a jednoczesnie mog¹ respic sie na max polu
			m_x = rand()%24 + 5;	
		}
		else
		{
			m_y = rand()%5 + 6; 
			m_x = rand()%14 + 15;	
		}

		if(map->getField(m_x,m_y)->getFieldType() == BLANK && map->getField(m_x,m_y)->getItemType() == NO_ITEM)
		{
			r_x = m_x*32 + 48;
			r_y = m_y*32 + 204;
			monster[i]->setX(r_x);
			monster[i]->setY(r_y);
			monster[i]->setType(levelMonster);
			monster[i]->setIsActive(true);
			monster[i]->setAnimDeathState(true);//animacja smierci potwora moze zostac wykonana
			monster[i]->setAnimStep(0);
		//	cout<<"wylosowalem potwora nr: "<<i<<" typu "<<levelMonster<<" -> wsp x,y: "<<m_x<<" "<<m_y<<endl;//testowe
			i++;
		}
	}
}






