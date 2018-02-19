#include "pch.h"

ShaderProgram::ShaderProgram(const char* vertFile, const char* fragFile)
{
	Init(vertFile, fragFile);
}

ShaderProgram::ShaderProgram(eShaderTypes type)
{
	m_VertString = m_Factory->CreateVertexShader(type);
	m_FragString = m_Factory->CreateFragmentShader(type);
	Init("","");
}

ShaderProgram::~ShaderProgram()
{
	CleanUp();
	delete m_Factory;
}

bool ShaderProgram::Init(const char* vertFile, const char* fragFile)
{
	if (m_VertString == 0 || m_FragString == 0)
	{
		// load files into strings
		m_VertString = LoadCompleteFile(vertFile, 0);
		m_FragString = LoadCompleteFile(fragFile, 0);
	}
	else
	{
		// factory created shaderstrings
	}

	if (m_VertString == 0 || m_FragString == 0)
	{
		OutputMessage("\nShaderProgram: Init() encountered load errors-> NULL shaderString!");
		assert(0);
		return false;
	}

	// compile shaders
	m_VertShaderHandle = CompileShader(GL_VERTEX_SHADER, m_VertString);
	m_FragShaderHandle = CompileShader(GL_FRAGMENT_SHADER, m_FragString);

	if (m_VertShaderHandle == 0 || m_FragShaderHandle == 0)
	{
		CleanUp();
		OutputMessage("\nShaderProgram: Init() encountered compile errors-> See compile error!");
		assert(0);
		return false;
	}

	// link shaders
	m_ProgramHandle = glCreateProgram();
	glAttachShader(m_ProgramHandle, m_VertShaderHandle);
	glAttachShader(m_ProgramHandle, m_FragShaderHandle);

	glLinkProgram(m_ProgramHandle);

	GLint success;
	glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(m_ProgramHandle, 512, NULL, infoLog);
		OutputMessage("\nShaderProgram: Init() linking error-> ");
		OutputMessage(infoLog); // OpenGL message
		assert(0);
		return false;
	}

	glDeleteShader(m_VertShaderHandle); // no longer needed
	glDeleteShader(m_FragShaderHandle);

	return true;
}

void ShaderProgram::CleanUp()
{
	if (m_VertString)
		delete[] m_VertString;
	if (m_FragString)
		delete[] m_FragString;

	glDetachShader(m_ProgramHandle, m_VertShaderHandle);
	glDetachShader(m_ProgramHandle, m_FragShaderHandle);

	if (m_VertShaderHandle)
		glDeleteShader(m_VertShaderHandle);
	if (m_FragShaderHandle)
		glDeleteShader(m_FragShaderHandle);
	if (m_ProgramHandle)
		glDeleteProgram(m_ProgramHandle);

	m_VertString = 0;
	m_FragString = 0;

	m_VertShaderHandle = 0;
	m_FragShaderHandle = 0;
	m_ProgramHandle = 0;
}

GLuint ShaderProgram::CompileShader(GLenum shaderType, const char* shaderString)
{
	GLuint shaderHandle = glCreateShader(shaderType);
	glShaderSource(shaderHandle, 1, &shaderString, NULL);
	glCompileShader(shaderHandle);

	GLint success;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);

		char* shaderTypeString;
		if (shaderType == GL_VERTEX_SHADER)
			shaderTypeString = "GL_VERTEX_SHADER";
		else
			shaderTypeString = "GL_FRAGMENT_SHADER";

		OutputMessage("\nShaderProgram: CompileShader() %s compile error-> ", shaderTypeString);
		OutputMessage(infoLog); // OpenGL message
		assert(0);
	}

	return shaderHandle;
}
// uniform value assignment
// TODO:: look at adding error checking
// int
void ShaderProgram::SetUniformInt1(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_ProgramHandle, name), value);
}
void ShaderProgram::SetUniformInt2(const char* name, int value1, int value2)
{
	glUniform2i(glGetUniformLocation(m_ProgramHandle, name), value1, value2);
}
void ShaderProgram::SetUniformInt3(const char* name, int value1, int value2, int value3)
{
	glUniform3i(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3);
}
void ShaderProgram::SetUniformInt4(const char* name, int value1, int value2, int value3, int value4)
{
	glUniform4i(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3, value4);
}
// float
void ShaderProgram::SetUniformFloat1(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_ProgramHandle, name), value);
}
void ShaderProgram::SetUniformFloat2(const char* name, float value1, float value2)
{
	glUniform2f(glGetUniformLocation(m_ProgramHandle, name), value1, value2);
}
void ShaderProgram::SetUniformFloat3(const char* name, float value1, float value2, float value3)
{
	glUniform3f(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3);
}
void ShaderProgram::SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3, value4);
}
// matrices
void ShaderProgram::SetUniformMat4(const char* name, mat4* matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramHandle, name), 1, GL_FALSE, &matrix->m11);
}
void ShaderProgram::SetUniformMat4(const char* name, glm::mat4* matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramHandle, name), 1, GL_FALSE, glm::value_ptr(*matrix));
}