#pragma once
#include "Singleton.h"
#include <vector>

class CFileUtils : public CSingleton<CFileUtils>
{
public:
	int** LoadMatrix(int m, int n, std::string filePath);

	std::vector<std::string> split(const std::string& str, char ch);

	std::vector<std::string> loadFromFile(const std::string& filePath);
};