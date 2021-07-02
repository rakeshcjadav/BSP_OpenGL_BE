#include "Shader.h"
#include "Header.h"
#include <fstream>

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

unsigned int CShader::ShaderID()
{
	return m_shaderID;
}

CShader::CShader(ShaderType type, const string shaderName)
{
	GLuint shaderType = GL_VERTEX_SHADER;

	string shaderTypeName = "VERTEX";

	if (type == ShaderType::Vertex)
	{
		shaderType = GL_VERTEX_SHADER;
		shaderTypeName = "VERTEX";
	}
	else if (type == ShaderType::Fragment)
	{
		shaderType = GL_FRAGMENT_SHADER;
		shaderTypeName = "FRAGMENT";
	}

	string shaderSource = LoadShader(shaderName);

	const char * source = shaderSource.c_str();

	m_shaderID = glCreateShader(shaderType);
	glShaderSource(m_shaderID, 1, &source, NULL);
	glCompileShader(m_shaderID);

	int success;
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderTypeName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

CShader::~CShader()
{
	glDeleteShader(m_shaderID);
	m_shaderID = 0;
}

string CShader::LoadShader(string shaderName)
{
	// All shaders are put in specific folder
	string shaderFilePath = Utils::GetShaderPath();

	ifstream file(shaderFilePath.append(shaderName));
	string shaderSource;
	if (file.is_open())
	{
		string line;
		int lineNumber = 0;
		while (getline(file, line))
		{
			shaderSource += line + "\n";
		}
	}

	file.close();
	return shaderSource;
}