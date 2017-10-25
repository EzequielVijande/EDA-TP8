
#include "FileSearcher.h"

bool SearchFiles(vector<const char*>& paths_vector, const char*directory, const char* ext)
{
	path p(directory);
	string dir(directory);
	string result1;
	string name;
	string extension;
	unsigned int i = 0;
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
					paths_vector.push_back(name.c_str()); //Guarda el path en el vector.
					cout << paths_vector[i] << endl;
					i++;
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