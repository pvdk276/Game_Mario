#pragma once
#include "Singleton.h"
#include <string>

class CFileUtils : public CSingleton<CFileUtils>
{
public:
	int** LoadMatrix(int m, int n, std::string filePath);
};