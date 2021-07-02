#include "Program.h"
#include "Header.h"
#include "Shader.h"

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
	CShader* pVertexShader = CShader::CreateShader(CShader::ShaderType::Vertex, pDef->vertexShader);
	CShader* pFragmentShader = CShader::CreateShader(CShader::ShaderType::Fragment, pDef->fragmentShader);

	m_programID = glCreateProgram();

	AttachShader(pVertexShader);
	AttachShader(pFragmentShader);

	glLinkProgram(m_programID);

	int success;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::" << pDef->name << "::LINKING_FAILED\n" << infoLog << std::endl;
	}

	CShader::Destroy(pVertexShader);
	CShader::Destroy(pFragmentShader);
}

CProgram::~CProgram()
{
	m_programID = 0;
}

void CProgram::AttachShader(CShader* pShader)
{
	glAttachShader(m_programID, pShader->ShaderID());
}