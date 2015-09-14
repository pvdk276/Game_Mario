#pragma once
#include "Singleton.h"
#include <string>

class FileUtils : public Singleton<FileUtils>
{
public:
	int** LoadMatrix(int m, int n, std::string filePath);
};