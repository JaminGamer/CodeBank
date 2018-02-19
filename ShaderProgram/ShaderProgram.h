#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

// This class requires access to OpenGL functions.
// Also, ShaderProgram() currently relies on an external file
// string parse function.

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	/* Setup */
	bool Init(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir);
	GLuint ReCompileShader(GLenum shaderType, const char* shaderString);

	/* Utility */
	void Use() { glUseProgram(m_ProgramHandle); };
	void CleanUp();

	/* Getters + Setters */
	// Getters
	GLuint GetProgram() { return m_ProgramHandle; };

	/* Texture setup */
	void SetupTextures(GLuint textures[], int numTextures);

	/* uniform value assignment */
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
	void SetUniformMat4(const char* name, const GLfloat* matrix);

private:
	/* Variables */
	const char* m_VertString = 0;
	const char* m_FragString = 0;
	const char* m_GeoString = 0;

	// TODO: Add geometry shader
	GLuint m_VertShaderHandle = 0;
	GLuint m_FragShaderHandle = 0;
	GLuint m_GeoShaderHandle = 0;
	GLuint m_ProgramHandle = 0;

	/* Functionality */
	GLuint CompileShader(GLenum shaderType, const char* shaderString);
	GLuint LinkShaders(GLuint vert, GLuint frag, GLuint geo);
};

#endif //__SHADERPROGRAM_H__
