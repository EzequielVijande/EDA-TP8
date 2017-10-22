#include "Decode.h"

//const char * archivo = "Prueba.txt";

bool decode (const char * archivo)
{
	bool ret = true;

	int c;						//Variable para recorrer el archivo codificado
	int i = 0;					//Contador
	int state = WAITING_H;		
	
	unsigned char * out;
	char length[4];
	
	cout << "Cargando archivo" << endl;
	FILE * toDecode;
	fopen_s(&toDecode, archivo, "rb");
	
	if (toDecode != nullptr)
	{
		for (int j = 0; j < 4; j++)			//Tomo los 4 primeros bytes del archivo que representan
		{									//el largo de la imagen original
			length[j] = fgetc(toDecode);
		}

		if ((out = (unsigned char *)malloc((sizeof(char))*((int)length[0]) * 4)) != nullptr)
		{
			while ((c = fgetc(toDecode)) != EOF)
			{
				if (((char)c == 'H') && (state == WAITING_H))
				{
					state = WAITING_N;
				}
				else if (((char)c == 'N') && (state == WAITING_N))
				{
					state = WAITING_RED;
				}
				else if (state == WAITING_RED)
				{
					out[i] = (char)c;
					state = WAITING_GREEN;
					i++;
				}
				else if (state == WAITING_GREEN)
				{
					out[i] = (char)c;
					state = WAITING_BLUE;
					i++;
				}
				else if (state == WAITING_BLUE)
				{
					out[i++] = (char)c;
					out[i++] = 255;
					state = WAITING_H;
				}
			}

			lodepng_encode32_file(archivo, out, (int)length[0], (int)length[0]);
		}
		else
		{
			cout << "Error al decodificar el archivo" << endl;
			ret = false;
		}

		free(out);
	}
	else
	{
		cout << "Error al cargar el archivo" << endl;
		ret = false;		
	}

	fclose(toDecode);

	return ret;
}