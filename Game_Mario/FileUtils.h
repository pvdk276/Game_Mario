#pragma once
#include "Singleton.h"
#include <vector>

class CFileUtils : public CSingleton<CFileUtils>
{
public:
	
	//load matrix from a text file
	int** LoadMatrix(int m, int n, std::string filePath);

	//split a string into a vector of string by a char object
	std::vector<std::string> split(const std::string& str, char ch);

	//load a vector of string from a text file (object list, binary tree)
	std::vector<std::string> loadFromFile(const std::string& filePath);
};