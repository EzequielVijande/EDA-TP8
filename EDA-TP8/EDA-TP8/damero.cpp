#include "damero.h"



damero::damero()
{
}

void damero::toggleSelectImage(int numberOfImage)
{
	images[numberOfImage].toggleSelected();
}

void damero::refresh(void)
{
	for (int i = 0; i < (images.size()); i++)
	{
		////////////!!!
	}
}


damero::~damero()
{
}
