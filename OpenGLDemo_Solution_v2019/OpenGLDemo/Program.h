#pragma once
#include<string>
using namespace std;

// Forward Declaration
class CShader;
struct SProgramDef;

class CProgram
{
public:
	static CProgram* CreateProgram(const SProgramDef * pDef);
	static void Destroy(CProgram* program);

private:
	CProgram(const SProgramDef* pDef);
	~CProgram();

	void AttachShader(CShader* pShader);

private:
	unsigned int m_programID = 0;
};


struct SProgramDef
{
	string name;
	string vertexShader;
	string fragmentShader;

	SProgramDef(string _name, string _vertexShader, string _fragementShader)
	{
		name = _name;
		vertexShader = _vertexShader;
		fragmentShader = _fragementShader;
	}
};