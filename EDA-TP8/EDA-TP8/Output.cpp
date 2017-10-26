#include "Output.h"
#define FONT_COLOR "yellow"
#define FONT_SIZE 15
#define BACKGROUND_PATH "background.png" //Imagen de fondo
#define FONT_PATH "font.ttf"

#define WIDTH_HALO 10

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
	int dameroActual = damero_.getDameroActual();
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < (damero_).getImages().size()); i++)
	{
		posX = ((damero_).getImages())[i].getPosX();
		posY = ((damero_).getImages())[i].getPosY();
		al_draw_bitmap(((damero_).getImages())[i].GetBitmap(), posX, posY,0); //Chequar posiciones.
		al_draw_text(font, al_color_name(FONT_COLOR), posX+(IMAGE_SIZE_X/2.0), posY + IMAGE_SIZE_Y+10, ALLEGRO_ALIGN_CENTRE, (damero_.getImages())[i].getPath());
		if (((damero_).getImages())[i].wasSelected())
		{
			DrawHalo(posX, posY, sizeX, sizeY);
		}

	}
	//al_draw_bitmap((damero_.getBotons()[0]).GetBitmap(), (damero_.getBotons()[0]).getPosX(), (damero_.getBotons()[0]).getPosY(),0);
	//al_draw_bitmap((damero_.getBotons()[1]).GetBitmap(), (damero_.getBotons()[1]).getPosX(), (damero_.getBotons()[1]).getPosY(), 0);

	bool botonTouched = false;
	int inicio = 0;  //en principio, deseo tener en cuenta todo el vector de botones.
	int finish = (int) (damero_).getBotons().size();

	if ((damero_).getDameroActual() == 0) //primer damero
	{
		inicio = 1; //salteo el primer boton.
	}
	else if ((damero_).getDameroActual() == (damero_).getDameroMaximo()) //ultimo damero
	{
		finish--; //descarto el último boton.
	}
	for (int i = inicio; (i < finish) && (!botonTouched); i++)
	{
		al_draw_bitmap((damero_.getBotons()[i]).GetBitmap(), (damero_.getBotons()[i]).getPosX(), (damero_.getBotons()[i]).getPosY(), 0);
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
	al_draw_bitmap(background, 0, 0, 0);
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


void viewer::DrawHalo(double x, double y, double sizeX, double sizeY)
{
	ALLEGRO_BITMAP* current_target = al_get_target_bitmap();
	al_set_target_backbuffer(display);

	for (int i = 1; i <= WIDTH_HALO; i++)
	{
		al_draw_rectangle(x-i, y - i, x + sizeX + i, y + sizeY + i, al_map_rgb(0,255-i*20,0), 1.0);
	}

	al_set_target_bitmap(current_target);
}
