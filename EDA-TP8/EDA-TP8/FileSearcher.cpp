#include "FileSearcher.h"

bool SearchFiles(vector<string>& paths_vector, const char*directory, const char* ext)
{
	path p(directory);
	string dir(directory);
	string name;
	string extension;
	if (exists(p))
	{
		if (is_directory(p))
		{
			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
			{

				extension = itr->path().extension().string();
				if (strcmp(ext, (extension.c_str())) == 0)
				{
					name = (itr->path().parent_path().string()) + "/" + (itr->path().filename().string());
					paths_vector.push_back(name); //Guarda el path en el vector.
				}
			}
			return true;
		}
		else
		{
			return false; //No es directorio
		}

	}
	else
	{
		return false; //No existe el path recibido.
	}
}