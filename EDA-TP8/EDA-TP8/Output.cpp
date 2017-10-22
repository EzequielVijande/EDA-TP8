#include "Output.h"
#define FONT_COLOR "red"
#define FONT_SIZE 30

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
		init = InitializeResources(img_path, font_path, font_size, seagulls, n_seagulls);
	}

}

viewer:: ~viewer()
{
	if (init)
	{
		al_destroy_bitmap(background);
		al_destroy_font(font);
		al_destroy_display(display);
		destroy_images(seagull, FRAMES);
	}
}

bool viewer::IsInitOK(void)
{
	return init;
}

void viewer::UpdateDisplay(bird* birds, unsigned int bird_count)
{
	ALLEGRO_BITMAP* current_target = al_get_target_bitmap(); //guarda el target actual para no perderlo.

	al_set_target_backbuffer(display);
	al_draw_bitmap(background, 0.0, 0.0, 0);
	unsigned int offset = 0;
	double direction = 0.0;
	for (unsigned int i = 0; i < bird_count; i++)
	{
		offset = ((birds + i)->getSecuence());
		if (offset > 15)
		{
			offset = 0;
		}
		direction = ((birds + i)->getDir());
		if ((direction>90) && (direction<270))
		{
			al_draw_bitmap(seagull[offset], (((birds + i)->getPos()).getX())*(UNIT), (((birds + i)->getPos()).getY())*(UNIT), ALLEGRO_FLIP_HORIZONTAL);

		}
		else
		{
			al_draw_bitmap(seagull[offset], (((birds + i)->getPos()).getX())*(UNIT), (((birds + i)->getPos()).getY())*(UNIT), 0);
		}
	}
	PrintText(birds);

	al_set_target_bitmap(current_target);
}

void viewer::PrintText(bird* birds)
{
	al_draw_textf(font, al_color_name(FONT_COLOR), 0, (height - (UNIT - 2))*(UNIT), ALLEGRO_ALIGN_LEFT, "Speed: %d", (birds->getSpeed())); //imprime la velocidad
	al_draw_text(font, al_color_name(FONT_COLOR), 0, (height - (UNIT - 2) / 1.5)*(UNIT), ALLEGRO_ALIGN_LEFT, "++: 's'"); //imprime como incrementar
	al_draw_text(font, al_color_name(FONT_COLOR), 0, (height - (UNIT - 2) / 2.5)*(UNIT), ALLEGRO_ALIGN_LEFT, "--: 'c'"); //imprime como decrementar

	al_draw_textf(font, al_color_name(FONT_COLOR), ((width / 2.0))*(UNIT), (height - (UNIT - 2))*(UNIT), ALLEGRO_ALIGN_CENTER, "Max Jiggle: %d", (birds->getMaxRandomJiggle())); //imprime el randomJiggle maximo
	al_draw_text(font, al_color_name(FONT_COLOR), ((width / 2.0))*(UNIT), (height - (UNIT - 2) / 1.5)*(UNIT), ALLEGRO_ALIGN_CENTER, "++: 'j'"); //imprime como incrementar
	al_draw_text(font, al_color_name(FONT_COLOR), ((width / 2.0))*(UNIT), (height - (UNIT - 2) / 2.5)*(UNIT), ALLEGRO_ALIGN_CENTER, "--: 'g'"); //imprime como decrementar


	al_draw_textf(font, al_color_name(FONT_COLOR), (width)*(UNIT), (height - (UNIT - 2))*(UNIT), ALLEGRO_ALIGN_RIGHT, "Eye Sight: %d", (birds->getEyeSight())); //imprime el eyesight
	al_draw_text(font, al_color_name(FONT_COLOR), (width)*(UNIT), (height - (UNIT - 2) / 1.5)*(UNIT), ALLEGRO_ALIGN_RIGHT, "++: 'e'"); //imprime como incrementar
	al_draw_text(font, al_color_name(FONT_COLOR), (width)*(UNIT), (height - (UNIT - 2) / 2.5)*(UNIT), ALLEGRO_ALIGN_RIGHT, "--: 'b'"); //imprime como decrementar


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

bool viewer::InitializeResources(char* path, char* font_path, unsigned int font_size, char** seagulls, unsigned int n_seagulls)
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
	for (unsigned int i = 0; i < n_seagulls; i++)
	{
		seagull[i] = load_image_at_size(seagulls[i], BIRD_SIZE, BIRD_SIZE);
		if ((seagull[i]) == nullptr)
		{
			al_destroy_display(display);
			al_destroy_bitmap(background);
			destroy_images(seagull, i);
			return false;
		}
	}
	font = al_load_ttf_font(font_path, font_size, 0);
	if (font == NULL)
	{
		al_destroy_display(display);
		al_destroy_bitmap(background);
		destroy_images(seagull, n_seagulls);
		return false;
	}
	return true;

}
