#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BITMAP_COUNT 25 //ilosc plikow z zasobami
#define FONT_COUNT 4
#define SAMPLE_COUNT 33

#define FPS 60 //timery sterowania
#define frameFPS 15 //timery animacji

#define MAP_UP 204 //wspolrzedne krawedzi mapy:
#define MAP_DOWN 524
#define MAP_LEFT 48
#define MAP_RIGHT 944

#define MAP_X 29 //macierz mapy
#define MAP_Y 11

namespace gameTypes
{
	enum FieldType //elementy mapy
	{ 
		BLANK, HARD_BRICK, SOFT_BRICK, EXPLODED_BRICK, EXPLOSION
	}; 

	enum ItemType //rodzaje itemów + drzwi
	{ 
		NO_ITEM, ITEM_L1, ITEM_L2, ITEM_L3, ITEM_L4, ITEM_L5, DOOR
	}; 

	enum MonsterType //przecwinicy
	{ 
		JELLY, TOXIN, BAD_BRICK, GHOST, BOSS 
	}; 
	
	enum GameScreen //ekrany gry
	{ 
		NULL_SCREEN, MAIN_MENU_SCREEN, ABOUT_SCREEN, 
		OPTIONS_SCREEN, VIEW_CONTROL_SCREEN, SET_CONTROL_SCREEN, 
		CHALLENGE_SCREEN, PAUSE_MENU_SCREEN, 
		GAME_OVER_SCREEN, COMPLETE_SCREEN, INTRO_SCREEN
	}; 

	enum BombState //stany bomby
	{
		NO_BOMB, ONE_BOMB, TWO_BOMBS
	};
	
	enum Direction //kierunki ruchu
	{
		DOWN, UP, LEFT, RIGHT
	};

	//zasoby
	enum Bitmap
	{
		B_HARD_BRICK, B_SOFT_BRICK, B_BCK_FRAME1, B_BCK_FRAME2, B_PLAYER,
		B_BLANK, B_BOMB, B_ITEM1, B_ITEM2, B_ITEM3, B_ITEM4, B_ITEM5,
		B_DOOR_C, B_DOOR_O, B_BCK_INTERFACE, B_JELLY, B_TOXIN, B_BAD_BRICK, B_GHOST, B_BOSS, B_SOFT_BRICK_BURN,
		B_QUEST_DONE, B_QUEST_IN_PROGRESS, B_PLAYER_DEATH, B_EXPLOSION
	};
	enum Font
	{
		F_SMALL, F_NORMAL, F_BIG, F_MICRO
	};

	enum Sample
	{
		S_MAIN_MENU, S_ROUND1, S_ROUND2,S_ROUND3, S_ROUND4, S_ROUND5,
		S_MOVE_LR, S_MOVE_UD, S_PUT_BOMB_OK, S_PUT_BOMB_OK_DET, S_PUT_BOMB_OK_DET2, S_PUT_BOMB_ERR, S_BOOM1, S_BOOM2, S_BOOM3,
		S_TAKE_ITEM1, S_TAKE_ITEM2, S_TAKE_ITEM3, S_TAKE_ITEM4, S_TAKE_ITEM5, S_MENU_SELECT1, S_MENU_SELECT2, S_LOW_TIME,
		S_ROUND_COMPLETE, S_BAD_TIME, S_U_DIE, S_LIFE_LOST, S_MON_DIE, S_LAST_MON, S_COMPLETE1, S_COMPLETE2, S_DMG_BOSS, S_DEATH_BOSS
	};

	
	struct GameControls //opcje gry
	{
		int up;
		int down;
		int right;
		int left;
		int bomb;
		int detonate;
		int pause;
		bool sound;
	};
}
