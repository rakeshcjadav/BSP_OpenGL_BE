#include "Shader.h"

CShader* CShader::CreateShader(ShaderType type, const string shaderName)
{
	CShader* pShader = new CShader(type, shaderName);
	return pShader;
}

void CShader::Destroy(CShader* pProgram)
{
	delete pProgram;
	pProgram = nullptr;
}

CShader::CShader(ShaderType type, const string shaderName)
{
	GLuint shaderType = GL_VERTEX_SHADER;

	if (type == ShaderType::Vertex)
		shaderType = GL_VERTEX_SHADER;
	else if(type == ShaderType::Fragment)
		shaderType = GL_FRAGMENT_SHADER;

	string shader = LoadShader(shaderName);

	m_shaderID = glCreateShader(shaderType);
}

CShader::~CShader()
{
	m_shaderID = 0;
}