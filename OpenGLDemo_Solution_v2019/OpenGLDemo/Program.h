#pragma once
#include "Header.h"

// Forward Declaration
struct SProgramDef;

class CProgram
{
public:
	static CProgram* CreateProgram(const SProgramDef * pDef);
	static void Destroy(CProgram* program);

private:
	CProgram(const SProgramDef* pDef);
	~CProgram();

private:
	GLuint m_programID = 0;
};


struct SProgramDef
{
	std::string name;
	std::string vertexShader;
	std::string fragmentShader;

	SProgramDef(string _name, string _vertexShader, string _fragementShader)
	{
		name = _name;
		vertexShader = _vertexShader;
		fragmentShader = _fragementShader;
	}
};