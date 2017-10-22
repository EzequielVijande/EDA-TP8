#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>
#include "Imagenes.h"
#include "damero.h"

#define UNIT 1
class viewer //Se ocupa de todo lo relacionado con el output de la simulacion
{
public:
	viewer(unsigned int width_=1000, unsigned int height_=600);
	~viewer();
	void UpdateDisplay(damero& damero_);
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
	bool InitializeResources(char* image, char* font_path, unsigned int font_size);
	void PrintText(damero& damero_); //falta definir
	void PrintSelected(bool selected_state); //dibuja el marco alrededor de una imagen seleccionada

};