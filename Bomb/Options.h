#pragma once
#include "Menu.h"

class Options: public Menu
{
	public:
		Options(ALLEGRO_COLOR color, bool soundOpt);
		~Options(void);
		void show();
		GameScreen control();
		bool getNewSoundOptions() const;
	private:
		bool soundOpt;
};

