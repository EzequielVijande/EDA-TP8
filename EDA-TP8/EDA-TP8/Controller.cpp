#include "Controller.h"

controller::controller(viewer & v)
{
	init = true;
	exit = false;
	if (!al_install_keyboard())
	{
		init = false;
		exit = false;
	}
	if (!al_install_mouse())
	{
		init = false;
		exit = false;
	}
	ev_queue = al_create_event_queue();
	if (ev_queue == NULL)
	{
		init = false;
		exit = true;
	}
	else if(init)
	{
		al_register_event_source(ev_queue, al_get_display_event_source(v.GetDisplay()));
		al_register_event_source(ev_queue, al_get_mouse_event_source());
		al_register_event_source(ev_queue, al_get_keyboard_event_source());
		

	}
}

controller::~controller()
{
	al_destroy_event_queue(ev_queue);
}

bool controller::IsInitOK()const
{
	return init;
}

void controller::dispatch(viewer& v, damero& d)
{
	ALLEGRO_EVENT ev;
	al_get_next_event(ev_queue, &ev);
	switch (ev.type)
	{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			exit = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (ev.keyboard.keycode) //Para cada uno de estos casos debe actualizarse el display.
			{
				case ALLEGRO_KEY_A:
					d.selectAllImages();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_N:
					d.unSelectAllImages();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_1:
					(d.getImages())[0].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_2:
					(d.getImages())[1].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_3:
					(d.getImages())[2].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_4:
					(d.getImages())[3].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_5:
					(d.getImages())[4].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_6:
					(d.getImages())[5].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_7:
					(d.getImages())[6].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_8:
					(d.getImages())[7].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_9:
					(d.getImages())[8].toggleSelected();
					al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
					v.UpdateDisplay(d);
					al_flip_display(); //Lom uestra en pantalla.
					break;

				case ALLEGRO_KEY_ENTER:
					if (d.wasSomethingSelected()) //esta funcion realiza un for, es posible que convenga sacar esta función y utilizar el mismo for 
					{                             //para poner las funciones de compripmir
						//Correr el algoritmo de compresion para cada imagen
						//seleccionada.
					}
					break;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			d.touchDamero((int)ev.mouse.x, (int)ev.mouse.y);
			al_set_target_backbuffer(v.GetDisplay()); //Actualiza el display
			v.UpdateDisplay(d);
			al_flip_display(); //Lom uestra en pantalla.
			break;
		
	}
}

bool controller::GetExit()const
{
	return exit;
}