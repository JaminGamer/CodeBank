#ifndef __MESH_H__
#define __MESH_H__

struct VertexData;
class GameObject;
class CameraObject;
class ShaderProgram;

typedef void (Mesh::*MeshFunction)(); // Draw function

class Mesh
{
public:
	Mesh();
	~Mesh();

	/* Setup */
	void BufferMeshData(int numVerts, VertexData* verts, int numIndices, unsigned int* indices);
	void SetupAttributes(ShaderProgram* shader);

	/* Draw */
	void Draw() { (this->*m_DrawFunc)(); }; // Call appropriate Draw() function

	/* Mesh creation */
	// defined in MeshShapes.cpp
	static Mesh* CreateBox(vec2 size);
	static Mesh* CreateCircle(float radius, unsigned int points, vec2 UVScale);
	static Mesh* CreateCube(vec3 size, vec2 UVScale = 1.0f, bool invertFaces = false);
	static Mesh* CreatePlane(vec2 size, vec2 NumOfVerts, vec2 UVScale);
	static Mesh* ImportOBJMesh(const char* fileDirectory, vec3 objScale = 1.0f, vec2 UVScale = 1.0f, bool invertFaces = false);

	/* Mesh data assignment */
	// defined in MeshShapes.cpp
	void GenerateBox(vec2 size);
	void GenerateCube(vec3 size);

	/* Mesh modifications */
	// helpers defined in MeshHelpers.cpp
	void ScaleUVCOORDS(VertexData verts[], int numVerts, vec2 UVScale);
	void CalculateXZUVCoords(VertexData vertArray[], int numVertices);
	void CalculateUVCoords(std::vector<VertexData> &verts);
	void CalculateUVCoords(VertexData verts[], int numVertices);
	void ScaleVertices(VertexData verts[], int numVerts, vec3 scale);

	void PaintObject(std::vector<VertexData> &verts, vec4 color); // vertex color
	void InvertFaces(unsigned int oldIBO[], unsigned int arraySize); // reverse winding order

	/* Getters + Setters */

	/* Cleanup */
	void DestroyMesh(); // Used for assigning new data to an already initialize mesh

private:
	/* Handles */
	GLuint m_VBO = 0;
	GLuint m_EBO = 0;
	GLuint m_VAO = 0;

	/* Variables */
	GLuint m_VertCount = 0;
	GLuint m_IndexCount = 0;
	GLenum m_PrimitiveType = GL_TRIANGLES;

	/* Draw functionality */
	MeshFunction m_DrawFunc = NULL;

	void DrawElements(); // Use IBO
	void DrawArrays(); // Draw raw vertex data
};

#endif //__MESH_H__
