#pragma once
//Asume que se inicializo Allegro
//Modulo que se ocupa de manejar los eventos y llamar
//A las funcione necesarias.
#include<allegro5\allegro.h>
#include"Output.h"
#include"damero.h"

class controller {
public:
	controller(viewer&);
	~controller();
	void dispatch(ALLEGRO_EVENT ev, damero& d);
	bool IsInitOK();

private:
	ALLEGRO_EVENT_QUEUE* ev_queue;
	bool init;
	bool exit;
};