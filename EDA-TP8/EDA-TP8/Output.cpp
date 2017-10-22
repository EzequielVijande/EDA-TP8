#include "Output.h"
#define FONT_COLOR "red"
#define FONT_SIZE 30
#define BACKGROUND_PATH "background.png" //Imagen de fondo
#define FONT_PATH "font.ttf"

bool InitializeAllegroOutput(void);
//Inicializa los  addons necesarios de allegro para
//utilizar el modulo de output.




viewer::viewer(unsigned int width_, unsigned int height_)
{
	width = width_;
	height = height_;
	font_size = FONT_SIZE;


	init = InitializeAllegroOutput();
	if (init)
	{
		init = InitializeResources(BACKGROUND_PATH, FONT_PATH, font_size);
	}

}

viewer:: ~viewer()
{
	if (init)
	{
		al_destroy_bitmap(background);
		al_destroy_font(font);
		al_destroy_display(display);
	}
}

bool viewer::IsInitOK(void)
{
	return init;
}

void viewer::UpdateDisplay(damero& damero_)
{
	ALLEGRO_BITMAP* current_target = al_get_target_bitmap(); //guarda el target actual para no perderlo.

	al_set_target_backbuffer(display);
	al_draw_bitmap(background, 0.0, 0.0, 0);
	
	PrintText(damero_);
	//Falta agregar las funciones que dibujan de los Image descriptors.

	al_set_target_bitmap(current_target);
}

void viewer::PrintText(damero& damero_)
{
	//Falta completar una vez que quede definido como van a ser las posiciones
	//de las imagenes y imprimir el contorno de si fue seleccionada.

}
bool InitializeAllegroOutput(void)
{
	if (!al_init_image_addon())
	{
		return false;
	}
	if (!al_init_font_addon())
	{
		return false;
	}
	if (!al_init_ttf_addon())
	{
		return false;
	}

	return true;
}
ALLEGRO_DISPLAY* viewer::GetDisplay(void)
{
	return display;
}

bool viewer::InitializeResources(char* path, char* font_path, unsigned int font_size)
{
	display = al_create_display(width*(UNIT), height*(UNIT));
	if (display == NULL)
	{
		return false;
	}


	background = load_image_at_size(path, width*(UNIT), height*(UNIT));
	if (background == nullptr)
	{
		al_destroy_display(display);
		return false;
	}
	
	font = al_load_ttf_font(font_path, font_size, 0);
	if (font == NULL)
	{
		al_destroy_display(display);
		al_destroy_bitmap(background);
		return false;
	}
	return true;

}

void viewer::PrintSelected(bool selected_state)
{

}
