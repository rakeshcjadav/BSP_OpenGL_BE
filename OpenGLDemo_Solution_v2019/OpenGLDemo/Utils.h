#pragma once
#include <string>

using namespace std;

class Utils
{
public:
	static string GetMediaPath();
	static string GetTexturePath();
	static string GetShaderPath();
private:
	Utils() = delete;
	~Utils() = delete;
};