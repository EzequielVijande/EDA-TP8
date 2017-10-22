#include "Output.h"
#define FONT_COLOR "red"
#define FONT_SIZE 30
#define BACKGROUND_PATH "background.png" //Imagen de fondo
#define FONT_PATH "font.ttf"

#define WIDTH_HALLO 10

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
	
	PrintDamero(damero_);

	al_set_target_bitmap(current_target);
}

void viewer::PrintDamero(damero & damero_)
{
	int posX = 0;
	int posY = 0;
	int sizeX = damero_.getSizeX();
	int sizeY = damero_.getSizeY();
	for (int i = 0; i < (damero_).getImages().size(); i++)
	{
		posX = ((damero_).getImages())[i].getPosX();
		posY = ((damero_).getImages())[i].getPosY();
		al_draw_scale_bitmap(posX, posY, sizeX, sizeY); //arreglar esta funcion
		al_draw_text(FONT_PATH, FONT_COLOR, posX, posY + ((damero_).getMargenY() / 3), 0, (damero_.getImages())[i].getPath());
		if (((damero_).getImages())[i].wasSelected())
		{
			DrawHalo(posX, posY, sizeX, sizeY);
		}

	}
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
	if (!al_init_primitives_addon())
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


void viewer::DrawHalo(int x, int y, int sizeX, int sizeY)
{
	ALLEGRO_BITMAP* current_target = al_get_target_bitmap();
	al_set_target_backbuffer(display);

	for (int i = 1; i <= WIDTH_HALO; i++)
	{
		al_draw_rectangle(x-i, y - i, x + sizeX + i, y + sizeY + i, al_map_rgb(0,255-(i*20),0), 1.0);
	}

	al_set_target_bitmap(current_target);
}
