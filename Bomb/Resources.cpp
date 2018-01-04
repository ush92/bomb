#include "Resources.h"

Resources::Resources(void)
{
	bitmap[B_HARD_BRICK] = al_load_bitmap("res/images/hardBrick.png");
	bitmap[B_SOFT_BRICK] = al_load_bitmap("res/images/softBrick.png");
	bitmap[B_BCK_FRAME1] = al_load_bitmap("res/images/backgroundFrameBitmap.png");
	bitmap[B_BCK_FRAME2] = al_load_bitmap("res/images/backgroundFrameBitmap2.png");
	bitmap[B_BCK_INTERFACE] = al_load_bitmap("res/images/backgroundInterface.png");
	bitmap[B_PLAYER] = al_load_bitmap("res/images/player.png");
	bitmap[B_BLANK] = al_load_bitmap("res/images/blankField.png");
	bitmap[B_BOMB] = al_load_bitmap("res/images/bomb.png");
	bitmap[B_ITEM1] = al_load_bitmap("res/images/item1.png");
	bitmap[B_ITEM2] = al_load_bitmap("res/images/item2.png");
	bitmap[B_ITEM3] = al_load_bitmap("res/images/item3.png");
	bitmap[B_ITEM4] = al_load_bitmap("res/images/item4.png");
	bitmap[B_ITEM5] = al_load_bitmap("res/images/item5.png");
	bitmap[B_DOOR_C] = al_load_bitmap("res/images/doorClosed.png");
	bitmap[B_DOOR_O] = al_load_bitmap("res/images/doorOpen.png");
	bitmap[B_JELLY] = al_load_bitmap("res/images/mon1.png");
	bitmap[B_TOXIN] = al_load_bitmap("res/images/mon2.png");
	bitmap[B_BAD_BRICK] = al_load_bitmap("res/images/mon3.png");
	bitmap[B_GHOST] = al_load_bitmap("res/images/mon4.png");
	bitmap[B_BOSS] = al_load_bitmap("res/images/boss.png");
	bitmap[B_SOFT_BRICK_BURN] = al_load_bitmap("res/images/softBrickExploded.png");
	bitmap[B_QUEST_DONE] = al_load_bitmap("res/images/questdone.png");
	bitmap[B_QUEST_IN_PROGRESS] = al_load_bitmap("res/images/questinprogress.png");
	bitmap[B_PLAYER_DEATH] = al_load_bitmap("res/images/playerDeath.png");
	bitmap[B_EXPLOSION] = al_load_bitmap("res/images/explosion.png");

	
	font[F_SMALL] = al_load_font("res/fonts/imagine_font.ttf", 30, NULL );
	font[F_NORMAL] = al_load_font("res/fonts/imagine_font.ttf", 70, NULL );
	font[F_BIG] = al_load_font("res/fonts/imagine_font.ttf", 165, NULL );
	font[F_MICRO] = al_load_font("res/fonts/visitor2.ttf", 14, NULL);

	sample[S_MAIN_MENU] = al_load_sample("res/samples/mainMenuTheme.ogg");
	sample[S_ROUND1] = al_load_sample("res/samples/round1.ogg");
	sample[S_ROUND2] = al_load_sample("res/samples/round2.ogg");
	sample[S_ROUND3] = al_load_sample("res/samples/round3.ogg");
	sample[S_ROUND4] = al_load_sample("res/samples/round4.ogg");
	sample[S_ROUND5] = al_load_sample("res/samples/round5.ogg");
	sample[S_MOVE_LR] = al_load_sample("res/samples/moving_l_r.wav");
	sample[S_MOVE_UD] = al_load_sample("res/samples/moving_u_d.wav");
	sample[S_PUT_BOMB_OK] = al_load_sample("res/samples/putbomb1.wav");
	sample[S_PUT_BOMB_OK_DET] = al_load_sample("res/samples/putbomb2.wav");
	sample[S_PUT_BOMB_OK_DET2] = al_load_sample("res/samples/putbomb2b.wav");
	sample[S_PUT_BOMB_ERR] = al_load_sample("res/samples/bombError.wav");
	sample[S_BOOM1] = al_load_sample("res/samples/boomb1.wav");
	sample[S_BOOM2] = al_load_sample("res/samples/boomb2.wav");
	sample[S_BOOM3] = al_load_sample("res/samples/boomb3.wav");
	sample[S_TAKE_ITEM1] = al_load_sample("res/samples/item1.wav");
	sample[S_TAKE_ITEM2] = al_load_sample("res/samples/item2.wav");
	sample[S_TAKE_ITEM3] = al_load_sample("res/samples/item3.wav");
	sample[S_TAKE_ITEM4] = al_load_sample("res/samples/item4.wav");
	sample[S_TAKE_ITEM5] = al_load_sample("res/samples/item5.wav");
	sample[S_MENU_SELECT1] = al_load_sample("res/samples/select1.wav");
	sample[S_MENU_SELECT2] = al_load_sample("res/samples/select2.wav");
	sample[S_LOW_TIME] = al_load_sample("res/samples/low_timer.wav");
	sample[S_ROUND_COMPLETE] = al_load_sample("res/samples/Stage_Complete.wav");
	sample[S_BAD_TIME] = al_load_sample("res/samples/bad_time.wav");
	sample[S_U_DIE] = al_load_sample("res/samples/death1.wav");
	sample[S_LIFE_LOST] = al_load_sample("res/samples/lifelost.wav");
	sample[S_MON_DIE] = al_load_sample("res/samples/UkillMonster.wav");
	sample[S_LAST_MON] = al_load_sample("res/samples/kill_all_monster.wav");
	sample[S_COMPLETE1] = al_load_sample("res/samples/complete1.wav");
	sample[S_COMPLETE2] = al_load_sample("res/samples/complete2.wav");
	sample[S_DMG_BOSS] = al_load_sample("res/samples/damageLastBoss.wav");
	sample[S_DEATH_BOSS] = al_load_sample("res/samples/bossdeath.wav");
}

Resources::~Resources(void)
{
	for(int i=0; i < BITMAP_COUNT; i++)
	{
		al_destroy_bitmap(bitmap[i]);
	}

	for(int i=0; i < FONT_COUNT; i++)
	{
		al_destroy_font(font[i]);
	}
	
	for(int i=0; i < SAMPLE_COUNT; i++)
	{
		al_destroy_sample(sample[i]);
	}
}

