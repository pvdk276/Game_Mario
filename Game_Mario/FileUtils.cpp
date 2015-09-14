#include "FileUtils.h"
#include <fstream>

int** FileUtils::LoadMatrix(int m, int n, std::string filePath)
{
	int** matrix;
	matrix = new int*[m];
	for (int i = 0; i < m; i++)
	{
		matrix[i] = new int[n];
	}

	std::ifstream myfile;
	myfile.open(filePath);
	if (myfile.is_open())
	{
		std::string line;
		int i = 0;
		int j = 0;
		while (getline(myfile, line))
		{
			char* str1 = new char[line.length() + 1];
			strcpy_s(str1, line.length() + 1, line.c_str());
			char* str = strtok(str1, ",");
			while (str != NULL)
			{
				matrix[i][j] = atoi(str);
				j++;
				if (j == 205)
				{
					i++;
					j = 0;
				}
				str = strtok(NULL, ",");
			}
		}
	}
	return matrix;
}