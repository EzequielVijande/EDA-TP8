#pragma once
#include <vector>
#include "ImageDescriptor.h"
class damero
{
public:
	damero(); //falta completar, debo obtener el vector de imagenes a partir del constructor!!!
	void refresh(void); //falta completar
	void toggleSelectImage(int numberOfImage);
	~damero();
private:
	vector<ImageDescriptor> images;
};

