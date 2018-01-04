#include "Game.h"

Game::Game(void)
{
	gameWindow = new AllegroForm("BooMan"); //stworzenie okna gry
	loadConfig(); 
	setActiveGameScreen(INTRO_SCREEN);//informacja o pierwszym wyswietlonym oknie
	initializeGameComponents();
}

Game::~Game(void)
{
	al_destroy_sample_instance(mainMenuTheme);
	al_destroy_sample_instance(completeTheme);
	delete mainMenu;
	delete about;
	delete options;
	delete setControls; 
	delete viewControls; 
	delete challenge;
	delete gameWindow;
	delete intro;
	delete gameOver;
}

void Game::initializeGameComponents()
{
	//screeny	
	intro = new Intro(al_map_rgb(0,0,0));
	mainMenu = new MainMenu(al_map_rgb(200,70,70));
	about = new About(al_map_rgb(200,125,100));
	options = new Options(al_map_rgb(125,200,125),gameControls.sound);
	setControls = new SetControls(al_map_rgb(100,125,200));
	viewControls = new ViewControls(al_map_rgb(225,225,150));
	gameOver = new GameOver();
	complete = new Complete();
	challenge = new Challenge();

	mainMenuTheme = al_create_sample_instance(getInstance()->resources->sample[S_MAIN_MENU]);
	al_set_sample_instance_playmode(mainMenuTheme, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(mainMenuTheme, al_get_default_mixer());
	
	completeTheme = al_create_sample_instance(getInstance()->resources->sample[S_COMPLETE2]);
	al_set_sample_instance_playmode(completeTheme, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(completeTheme, al_get_default_mixer());
	isCompleteTheme = false;
}

void Game::loadConfig()//wczytanie opcji gry z pliku konfiguracyjnego.
{
	fstream testConfigFile; 
	testConfigFile.open( "config.cfg" );
	
	if(!testConfigFile.good()) //jezeli plik z jakiegos powodu by nie istnial tworzy domyslny i wtedy pobiera dane... 
	{
		ofstream newConfigFile( "config.cfg" );
		newConfigFile << "up "<< 23 <<endl;//w
		newConfigFile << "down "<< 19 <<endl;//s
		newConfigFile << "left "<< 1 <<endl;//a
		newConfigFile << "right "<< 4 <<endl;//d
		newConfigFile << "bomb "<< 75 <<endl;//space
		newConfigFile << "detonate "<< 215 <<endl;//true - dzwiek wl.
		newConfigFile << "pause "<< 59 <<endl;//esc
		newConfigFile << "sound "<< 1 <<endl;//true - dzwiek wl.
		newConfigFile.close();
	}
	testConfigFile.close();
	
	string temp1;//zmienne pomocnicze przy wczytywaniu danych z pliku.

	ifstream configFile( "config.cfg" );
	configFile >>temp1 >> gameControls.up; //temp1 jest po to zeby zapisac opis opcji. reszta to kod znaku allegro
	configFile >>temp1 >> gameControls.down;
	configFile >>temp1 >> gameControls.left;
	configFile >>temp1 >> gameControls.right;
	configFile >>temp1 >> gameControls.bomb;
	configFile >>temp1 >> gameControls.detonate;
	configFile >>temp1 >> gameControls.pause;
	configFile >>temp1 >> gameControls.sound;

	configFile.close();

	if(gameControls.sound)	//ustawienie dzwieku
	{
		al_set_mixer_gain(al_get_default_mixer(), 1);
	}
	else
	{
		al_set_mixer_gain(al_get_default_mixer(), 0);
	}
}

void Game::saveConfig(GameControls &gameControls) //zapisywanie konfigu do pliku
{
	ofstream newConfigFile( "config.cfg" );
	newConfigFile << "up "<< gameControls.up <<endl;//w
	newConfigFile << "down "<< gameControls.down <<endl;//s
	newConfigFile << "left "<< gameControls.left <<endl;//a
	newConfigFile << "right "<< gameControls.right <<endl;//d
	newConfigFile << "bomb "<< gameControls.bomb <<endl;//space
	newConfigFile << "detonate "<< gameControls.detonate <<endl;//space
	newConfigFile << "pause "<< gameControls.pause <<endl;//esc
	newConfigFile << "sound "<< gameControls.sound <<endl;//true - dzwiek wl.
	newConfigFile.close();
}

void Game::start()
{
	while(activeGameScreen)
	{
		updateGameScreen(); //NULL_SCREEN ma wartosc 0 wiec przerywa pêtle zamykaj¹c gre
	}
}

GameScreen Game::getActiveGameScreen() const
{
	return activeGameScreen;
}
	
void Game::setActiveGameScreen(GameScreen activeGameScreen)
{
	this->activeGameScreen = activeGameScreen;
}

void Game::updateGameScreen() 
{
	switch(getActiveGameScreen())
	{
		case NULL_SCREEN: //wyjscie z programu
			break;
		
		case INTRO_SCREEN:
			intro->show(); 
			setActiveGameScreen(intro->control());
			break;

		case MAIN_MENU_SCREEN:
			if(!isCompleteTheme) al_play_sample_instance(mainMenuTheme);
			mainMenu->show(); 
			setActiveGameScreen(mainMenu->control());	
			break;
		
		case ABOUT_SCREEN:
			about->show();	
			setActiveGameScreen(about->control());
			break;
		
		case OPTIONS_SCREEN:
			options->show();	
			setActiveGameScreen(options->control());
			gameControls.sound = options->getNewSoundOptions(); 
			saveConfig(gameControls); //zapis konfiguracji do pliku 
			break;
		
		case VIEW_CONTROL_SCREEN:
			viewControls->setNewControlOptions(gameControls);
			viewControls->show();
			setActiveGameScreen(viewControls->control());
			break;

		case SET_CONTROL_SCREEN:
			setControls->show();
			setActiveGameScreen(setControls->control());
			gameControls = setControls->getNewControlOptions();
			saveConfig(gameControls);
			break;

		case CHALLENGE_SCREEN: 
			isCompleteTheme = false;
			al_stop_sample_instance(mainMenuTheme);
			al_stop_sample_instance(completeTheme);
			challenge->setControls(gameControls);
			challenge->generateNewChallenge();
			setActiveGameScreen(challenge->update());
			break;

		case GAME_OVER_SCREEN:
			gameOver->show();
			setActiveGameScreen(gameOver->control());
			break;
			
		case COMPLETE_SCREEN:
			complete->setPoints(challenge->getPoints());
			complete->show();
			al_play_sample_instance(completeTheme);
			isCompleteTheme = true;
			setActiveGameScreen(complete->control());
			break;
			
		default:
			break;
	}
}