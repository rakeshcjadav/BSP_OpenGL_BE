#include "Program.h"

CProgram* CProgram::CreateProgram(const SProgramDef* pDef)
{
	CProgram* pProgram = new CProgram(pDef);
	return pProgram;
}

void CProgram::Destroy(CProgram* pProgram)
{
	delete pProgram;
	pProgram = nullptr;
}

CProgram::CProgram(const SProgramDef* pDef)
{
	m_programID = 0;
}

CProgram::~CProgram()
{
	m_programID = 0;
}