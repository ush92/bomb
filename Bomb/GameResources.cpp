#include "GameResources.h"

bool GameResources::instanceFlag = false;
GameResources* GameResources::gameResources = NULL;

GameResources::GameResources(void)
{
}

GameResources::GameResources(const GameResources & )
{
}

GameResources::~GameResources(void)
{
	if(instanceFlag)
	{
		delete getInstance()->resources;
		instanceFlag = false;
	}
}

GameResources* GameResources::getInstance()
{
	if(!instanceFlag)
    {
		gameResources = new GameResources();
		gameResources->resources = new Resources();
		instanceFlag = true;
		return gameResources;
    }
    else
    {
		return gameResources;
    }
}
