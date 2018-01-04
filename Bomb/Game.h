#pragma once
#include <fstream>
#include "GameTypes.h"
#include "AllegroForm.h"
#include "MainMenu.h"
#include "About.h"
#include "Options.h"
#include "SetControls.h"
#include "ViewControls.h"
#include "Challenge.h"
#include "GameResources.h"
#include "Intro.h"
#include "GameOver.h"
#include "Complete.h"

using namespace gameTypes;
using namespace std;

class Game :
	public GameResources
{
public:
	Game(void);
	~Game(void);
	void start();
private:
	GameScreen getActiveGameScreen() const;
	void setActiveGameScreen(GameScreen);
	void updateGameScreen();

	void initializeGameComponents(); 
	void initializeBitmaps();
	void loadConfig();
	void saveConfig(GameControls &gameControls);
	
	ALLEGRO_SAMPLE_INSTANCE *mainMenuTheme;	
	ALLEGRO_SAMPLE_INSTANCE *completeTheme;
	bool isCompleteTheme;
	
	GameScreen activeGameScreen; 
	
	AllegroForm *gameWindow; 
	GameControls gameControls;
		 
	//screeny 
	Intro *intro;
	MainMenu *mainMenu;	
	About *about;	
	Options *options;	
	SetControls *setControls; 
	ViewControls *viewControls; 
	GameOver *gameOver;
	Complete *complete;

	Challenge *challenge;
};