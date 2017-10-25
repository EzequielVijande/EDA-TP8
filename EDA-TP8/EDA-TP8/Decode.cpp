#include "Decode.h"

const char * archivo = "prueba1.met";
const char * archivo2 = "prueba1.png";

bool decode (const char * archivo)
//bool main (void)
{
	bool ret = true;

	unsigned int bytesCount = 0;
	int state = WAITING_N;
	int c;								//Variable para recorrer el archivo codificado
			
	
	unsigned char * bitmap;				//Buffer donde se guarda la imagen en formato RGBA temporalmente
										//para luego coficar
	unsigned char * tempbuff;			//Buffer donde se guarda la imagen en formato PNG temporalmente

	unsigned char lengthAux[4];
	uint32_t length;					//Variable para guardar el tamaño de la imagen
	
	cout << "Cargando archivo" << endl;
	
	FILE * toDecode;
	fopen_s(&toDecode, archivo, "rb");

	if (toDecode != nullptr)
	{
		for (int j = 0; j < 4; j++)			//Tomo los 4 primeros bytes del archivo que representan
		{									//el largo de la imagen original en pixeles
			lengthAux[j] = fgetc(toDecode);
		}
		length = ((uint32_t)lengthAux[0]);

		bitmap = (unsigned char *) malloc(length * length * 4);	//Por cada pixel guardo 4 bytes: RGBA

		if (bitmap != nullptr)
		{
			while ((c = fgetc(toDecode)) != EOF)
			{
				if ((char)c == 'H') 
				{
					state = WAITING_N;
				}
				else if (((char)c == 'N') && (state == WAITING_N))
				{
					state = WAITING_RED;
				}
				else if (state == WAITING_RED)
				{
					bitmap[bytesCount++] = (char)c;
					state = WAITING_GREEN;
				}
				else if (state == WAITING_GREEN)
				{
					bitmap[bytesCount++] = (char)c;
					state = WAITING_BLUE;
				}
				else if (state == WAITING_BLUE)
				{
					bitmap[bytesCount++] = (char)c;
					bitmap[bytesCount++] = 255;
					state = WAITING_N;
				}
			}

			lodepng_encode32(&tempbuff, (size_t *) &bytesCount, bitmap, length, length);

			FILE * decoded;
			fopen_s(&decoded, archivo2, "wb");

			if (decoded != nullptr)
			{
				for (unsigned int j = 0; j < bytesCount; j++)
				{
					fputc(tempbuff[j], decoded);
				}
			}
			else
			{
				cout << "Error al crear la imagen decodificada" << endl;
			}

			fclose(decoded);
		
		}
		else
		{
			cout << "Error al decodificar el archivo" << endl;
			ret = false;
		}

		free(bitmap);
	}
	else
	{
		cout << "Error al cargar el archivo" << endl;
		ret = false;		
	}

	fclose(toDecode);

	getchar();

	return ret;
}