#pragma once
#include<string>
using namespace std;

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

	unsigned int ShaderID();
private:
	CShader(ShaderType type, const string shaderName);
	~CShader();

	string LoadShader(string shaderName);

private:
	unsigned int m_shaderID;
};
