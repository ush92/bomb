#include "Camera.h"


Camera::Camera(void)
{
	mapScrollpx=0;
}


Camera::~Camera(void)
{
}

void Camera::update(float x)
{
	cameraPosition = -SCREEN_WIDTH/2 + x + 16; // -polowa ekranu + wspolrzedne gracza + polowa szer/wys gracza (16px)


	if(cameraPosition < 0) //jezeli pozycja kamery jest po lewej stronie punktu przesuwania
	{
		cameraPosition = 0; //to pozycja kamery bedzie sta³a (bo odejmuje sie 0)
		mapScrollpx = 0;
	}
	
	if(cameraPosition < 226)//jezeli pozycja kamery jest ponizej punktu granicznego(226) to przesuwaj obraz
	{
		al_identity_transform(&instance);
		al_translate_transform(&instance, -cameraPosition, 0); //y=0 blokuje w tym przypadku pionowy ruch kamery
		al_use_transform(&instance);
		mapScrollpx = cameraPosition;
	}
	else 
	{
		mapScrollpx = 224;
	}
}

float Camera::getMapScrollPx()
{
	return mapScrollpx;
}

void Camera::repair()
{
	for(int i=0; i<11; i++)
	{
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 16+mapScrollpx, 204 + i*32,NULL);//lewa
		al_draw_bitmap(getInstance()->resources->bitmap[B_HARD_BRICK], 752+mapScrollpx, 204 + i*32,NULL);//prawa
	}
	al_draw_filled_rectangle(0+mapScrollpx,0,16+mapScrollpx,600,al_map_rgb(0,0,0));//lewy czarny paseczek
	al_draw_filled_rectangle(784+mapScrollpx,0,800+mapScrollpx,600,al_map_rgb(0,0,0));//prawy czarny paseczek
}