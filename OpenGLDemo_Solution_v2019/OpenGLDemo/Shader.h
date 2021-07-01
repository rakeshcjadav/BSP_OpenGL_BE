#pragma once
#include "Header.h"

class CShader
{
public:
	enum class ShaderType
	{
		Fragment,
		Vertex
	};
public:
	static CShader* CreateShader(ShaderType type, const string shaderName);
	static void Destroy(CShader* program);

private:
	CShader(ShaderType type, const string shaderName);
	~CShader();

private:
	GLuint m_shaderID;
};
