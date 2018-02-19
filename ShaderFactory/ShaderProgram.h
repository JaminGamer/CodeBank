#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

class ShaderFactory;

class ShaderProgram
{
public:
	ShaderProgram(eShaderTypes type);
	ShaderProgram(const char* vertFile, const char* fragFile);
	ShaderProgram() {};
	~ShaderProgram();

	bool Init(const char* vertFile, const char* fragFile);
	void Use() { glUseProgram(m_ProgramHandle); };

	GLuint GetProgram() { return m_ProgramHandle; };

	void CleanUp();

	// uniform value assignment
	// int
	void SetUniformInt1(const char* name, int value);
	void SetUniformInt2(const char* name, int value1, int value2);
	void SetUniformInt3(const char* name, int value1, int value2, int value3);
	void SetUniformInt4(const char* name, int value1, int value2, int value3, int value4);
	// float
	void SetUniformFloat1(const char* name, float value);
	void SetUniformFloat2(const char* name, float value1, float value2);
	void SetUniformFloat3(const char* name, float value1, float value2, float value3);
	void SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4);
	// matrices
	void SetUniformMat4(const char* name, mat4* matrix);
	void SetUniformMat4(const char* name, glm::mat4* matrix);

private:
	GLuint CompileShader(GLenum shaderType, const char* shaderString);
	const char* m_VertString = 0;
	const char* m_FragString = 0;

	GLuint m_VertShaderHandle = 0;
	GLuint m_FragShaderHandle = 0;
	GLuint m_ProgramHandle = 0;

	ShaderFactory* m_Factory = new ShaderFactory();
};

#endif //__SHADERPROGRAM_H__
