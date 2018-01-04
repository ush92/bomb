#include "Interface.h"

Interface::Interface()
{
	
}

Interface::~Interface(void)
{

}

void Interface::show(float scrollPx) const
{	
	al_draw_filled_rectangle(48+scrollPx,44,752+scrollPx,172,color);
	for(int i=0; i<24; i++)
	{
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 16 + i*32 + scrollPx, 12, NULL);//gora
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 16 + i*32 + scrollPx, 556, NULL);//dol
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 16 + i*32 + scrollPx, 172, NULL);//przedzialka ;s
	}
	for(int i=0; i<16; i++)
	{
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 16 + scrollPx, 44 + i*32,NULL);//lewa
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 752 + scrollPx, 44 + i*32,NULL);//prawa
	}
	for(int i=0; i<4; i++)
	{
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 400 + scrollPx, 44 + i*32, NULL);//srodek1
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 496 + scrollPx, 44 + i*32, NULL);//srodek2
	}
	al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 432 + scrollPx, 76, NULL);//srodek3
	al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 464 + scrollPx, 76, NULL);//srodek4


	al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_FRAME1],scrollPx,0,NULL);
}

void Interface::update(float scrollPx, int roundID, int points, float timeLeft, string roundName, bool equipment, int monsterLeft, int hp)
{
	al_draw_filled_rectangle(48+scrollPx,44,752+scrollPx,172,color);
	al_draw_bitmap(getInstance()->resources->bitmap[B_BCK_INTERFACE], 48+scrollPx,44, NULL);//t³o
	for(int i=0; i<4; i++)
	{
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 400 + scrollPx, 44 + i*32, NULL);//srodek1
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 496 + scrollPx, 44 + i*32, NULL);//srodek2
	}
	al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 432 + scrollPx, 76, NULL);//srodek3
	al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 464 + scrollPx, 76, NULL);//srodek4

	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),64+ scrollPx,59,ALLEGRO_ALIGN_LEFT,"%d. %s",roundID, roundName.c_str());
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),64+ scrollPx,99,ALLEGRO_ALIGN_LEFT,"score:");
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),264+ scrollPx,99,ALLEGRO_ALIGN_LEFT,"%d",points);
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),64+ scrollPx,139,ALLEGRO_ALIGN_LEFT,"Time:");
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),264+ scrollPx,139,ALLEGRO_ALIGN_LEFT,"%0.f",timeLeft);

	//al_draw_filled_rectangle(432+scrollPx,44,464+scrollPx,76,color2);//ramka na ikonke potwora
	al_draw_bitmap_region(getInstance()->resources->bitmap[monBitmap],32,0,32,32,432+scrollPx,44,NULL);//wyswietlanie ikonki potwora
	if(roundID <= 3) 
	{
		al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),471+ scrollPx,51,ALLEGRO_ALIGN_LEFT,"%d",monsterLeft);
	}
	else if(roundID == 4) //w czwartej rundzie nie trzeba niczego zabijac zatem ilosc nie jest wyswietlana. zamiast tego elegancka kreseczka:p
	{
		al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),475+ scrollPx,51,ALLEGRO_ALIGN_LEFT,"-");
	}
	else //w piatej rundzie jest pokazane hp bossa
	{
		al_draw_textf(getInstance()->resources->font[F_MICRO],al_map_rgb(0,0,0),474+ scrollPx,45,ALLEGRO_ALIGN_LEFT,"%d",hp);
		al_draw_textf(getInstance()->resources->font[F_MICRO],al_map_rgb(0,0,0),474+ scrollPx,63,ALLEGRO_ALIGN_LEFT,"HP");
	}
	
	al_draw_textf(getInstance()->resources->font[F_SMALL],al_map_rgb(0,0,0),548+ scrollPx,59,ALLEGRO_ALIGN_LEFT,"Equipment");
	al_draw_filled_rectangle(559+scrollPx,95,720+scrollPx,127,color2);//ramka na eq
	for(int i=0;i<itemCount;i++)
	{
		al_draw_bitmap(getInstance()->resources->bitmap[7+i], 559+i*32+scrollPx, 95, NULL);//wyswietlanie itemów
	}
	
	if(equipment) //jezeli item zostanie wziêty
	{
		al_draw_bitmap(getInstance()->resources->bitmap[7+roundID-1], 559+(roundID-1)*32+scrollPx, 95, NULL);
		al_draw_textf(getInstance()->resources->font[F_MICRO],al_map_rgb(0,0,0),533+ scrollPx,135,ALLEGRO_ALIGN_INTEGER,"%s",roundText1.c_str());
		al_draw_textf(getInstance()->resources->font[F_MICRO],al_map_rgb(0,0,0),533+ scrollPx,154,ALLEGRO_ALIGN_INTEGER,"%s",roundText2.c_str());
		if(!monsterLeft || roundID == 4)
		{
			al_draw_bitmap(getInstance()->resources->bitmap[B_QUEST_DONE], 439 + scrollPx, 115, NULL);//otwarta klodka
		}
		else al_draw_bitmap(getInstance()->resources->bitmap[B_QUEST_IN_PROGRESS], 439 + scrollPx, 115, NULL);//zamknieta klodka
	}
	else al_draw_bitmap(getInstance()->resources->bitmap[B_QUEST_IN_PROGRESS], 439 + scrollPx, 115, NULL);//zamknieta klodka

	al_flip_display();
}

void Interface::setInterface(int roundID)
{
	switch(roundID)
	{
		case 1:
			color = al_map_rgb(140,210,140);
			color2 = al_map_rgb(166,236,166);
			monBitmap = B_JELLY;
			roundText1 = "You obtained roller-skates";
			roundText2 = "You are very fast now";
			break;

		case 2:
			color = al_map_rgb(120,160,200);
			color2 = al_map_rgb(146,186,226);
			monBitmap = B_TOXIN;
			roundText1 = "You obtained the B-napalm";
			roundText2 = "Range of your bombs is longer";
			break;
		
		case 3:
			color = al_map_rgb(130,110,180);
			color2 = al_map_rgb(156,136,206);
			monBitmap = B_BAD_BRICK;
			roundText1 = "You obtained an electro fuse";
			roundText2 = "Press detonate button to use it";
			break;
		
		case 4:
			color = al_map_rgb(120,120,120);
			color2 = al_map_rgb(136,136,136);
			monBitmap = B_GHOST;
			roundText1 = "You obtained the dispersion suit";
			roundText2 = "You can walk through obstacles";
			break;
		
		case 5:
			color = al_map_rgb(180,50,50);
			color2 = al_map_rgb(206,76,76);
			monBitmap = B_BOSS;
			roundText1 = "You obtained a double charge";
			roundText2 = "You can plant two bombs at once";
			break;
	}

	itemCount = roundID - 1;
}