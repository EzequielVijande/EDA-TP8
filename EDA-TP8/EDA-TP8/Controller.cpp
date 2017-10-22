#include "Controller.h"

controller::controller(viewer& v)
{
	init = true;
	exit = false;
	ev_queue = al_create_event_queue();
	if (ev_queue == NULL)
	{
		init = false;
	}
	else 
	{
		al_register_event_source(ev_queue, al_get_keyboard_event_source());
		al_register_event_source(ev_queue, al_get_display_event_source(v.GetDisplay()));
		al_register_event_source(ev_queue, al_get_mouse_event_source());

	}
}

controller::~controller()
{
	al_destroy_event_queue(ev_queue);
}

bool controller::IsInitOK()
{
	return init;
}

void controller::dispatch(ALLEGRO_EVENT ev, damero& d)
{
	double pos_x = 0.0;
	double pos_y = 0.0;
	switch (ev.type)
	{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			exit = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (ev.keyboard.keycode) //Para cada uno de estos casos debe actualizarse el display.
			{
				case ALLEGRO_KEY_A:
					//Selecciona todas las imagenes.
					break;
				case ALLEGRO_KEY_N:
					//deselecciona todas las imagenes.
					break;
				case ALLEGRO_KEY_1:
					//Selecciona la primera imagen.
					break;
				case ALLEGRO_KEY_2:
					//Selecciona la segunda imagen.
					break;
				case ALLEGRO_KEY_3:
					//Selecciona la tercera imagen.
					break;
				case ALLEGRO_KEY_4:
					//Selecciona la cuarta imagen
				case ALLEGRO_KEY_5:
					//Selecciona la quinta imagen.
					break;
				case ALLEGRO_KEY_6:
					//Selecciona la sexta imagen.
					break;
				case ALLEGRO_KEY_7:
					//Selecciona la septima imagen.
					break;
				case ALLEGRO_KEY_8:
					//Selecciona la octava imagen.
					break;
				case ALLEGRO_KEY_9:
					//Selecciona la novena imagen.
					break;
				case ALLEGRO_KEY_ENTER:
					//Verificar que hay alguna imagen seleccionada.
					//Correr el algoritmo de compresion para cada imagen
					//seleccionada.
					break;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
			//Habria que hacer una funcion que verifique si el click toco una
			//imagen, y luego llamar a las funciones adecuadas de imagedescriptor.
			break;
		
	}
}