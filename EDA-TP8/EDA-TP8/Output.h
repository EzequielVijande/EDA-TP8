#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>
#include "Imagenes.h"

#define UNIT 1
class viewer //Se ocupa de todo lo relacionado con el output de la simulacion
{
public:
	viewer(Damero& damero, unsigned int width_=1000, unsigned int height_=600);
	~viewer();
	void UpdateDisplay(Damero& damero, unsigned int damero_count);
	bool IsInitOK(void);
	ALLEGRO_DISPLAY* GetDisplay(void);

private:

	unsigned int height;
	unsigned int width;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP* background;
	ALLEGRO_FONT* font;
	double font_size;
	bool init;
	bool InitializeResources(char* image, char* font_path, unsigned int font_size, char** seagulls, unsigned int n_seagulls);
	void PrintText(Damero& damero);
	void PrintSelected();
	);

};