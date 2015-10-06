#include "FileUtils.h"
#include <fstream>
#include <sstream>
#include <string>


int** CFileUtils::LoadMatrix(int m, int n, std::string filePath)
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
				if (j == n)
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

std::vector<std::string> CFileUtils::split(const std::string& str, char ch)
{
	std::vector<std::string> result;
	if (str.length() > 0) //Neu gia tri truyen vao khac null thi tien hanh cat
	{
		std::stringstream stream(str);
		std::string item;
		while (getline(stream, item, ch))
		{
			if (item.length() > 0)
			{
				result.push_back(item);
			}
		}
	}
	return result;
}

std::vector<std::string> CFileUtils::loadFromFile(const std::string& filePath)
{
	std::ifstream* reader = new std::ifstream(filePath);
	std::string item;
	std::vector<std::string> result;
	if (reader->is_open())
	{
		while (!reader->eof())
		{
			std::getline(*reader, item);
			result.push_back(item);
		}
		reader->close();
	}
	return result;
}