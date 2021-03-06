#include "stdafx.h"

void RenderRoutine::Initialize()
{
	m_pParent->AddDrawRoutine(this);
	m_pRender = (RenderComponent*)m_pParent->GetComponent(Component_Render);
	SetDrawFunction();
}

void RenderRoutine::Draw(GameObject* cameraObject)
{
	this; // Debugging
	assert(m_pRender != nullptr); // safety check

	/* Variables */
	CameraComponent* t_pCamera = (CameraComponent*)cameraObject->GetComponent(Component_Camera);
	Mesh* t_pMesh = m_pRender->GetMesh();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	/* Safety check */
	if (t_pShader == nullptr) { return; } // nullptr*?
	// if (t_pMesh == nullptr) { return; } // nullptr*?

	/* Use Program */
	t_pShader->Use();

	// Lighting
	// if (m_LightingEnabled) { SetupLightingUniforms(); };

	for (uint i = 0; i < m_UniformSetupList.size(); i++)
	{
		(this->*m_UniformSetupList.at(i))(t_pCamera); // Call setup function
	}

	/* Draw */
    Model* t_Model = m_pRender->GetModel();
    if (t_Model)
    {
        t_Model->Draw();
    }
    else if(m_pRender->GetMesh())
    {
        t_pMesh->Draw();
    }
}
//// Private functions
void RenderRoutine::SetDrawFunction() // Assign function pointers and initialize values
{
	CheckforGLErrors(__FILE__, __LINE__);

	Mesh* t_pMesh = m_pRender->GetMesh();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	/* Safety check */
	// TODO: Setup NULL Meshes and Shaders for debugging
	if (t_pShader == nullptr) { return; } // nullptr*?
	if (t_pMesh == nullptr)
    {
        Model* t_Model = m_pRender->GetModel();
        if (t_Model)
        {
            t_Model->SetupMeshes(t_pShader);
        }
        else
        {
            return;
        }
    }
    else
    {
        /* Setup Shader() and Mesh() */
        t_pMesh->SetupShaderAttributes(t_pShader);
    }

	// TODO:: Improve conditions for assignments.
	/* Variables*/
	GLuint t_Texture = m_pRender->GetCurrentTexture(); // TODO: Handle more than 1 texture
	MaterialData* t_Material = m_pRender->GetMaterial();

	/* Uniforms */
	std::vector<std::string> t_Uniforms = t_pShader->GetUniformList();
	for (size_t i = 0; i < t_Uniforms.size(); i++) // Setup uniforms
	{
		// Color
		if (t_Uniforms.at(i) == "ObjectColor")
		{
			m_UniformSetupList.push_back(&RenderRoutine::SetupColorUniforms);
		}
		else if (t_Uniforms.at(i) == "WorldMat")
		{
			m_UniformSetupList.push_back(&RenderRoutine::Setup3DTransform);
		}
		else if (t_Uniforms.at(i) == "2DTransform")
		{
			m_UniformSetupList.push_back(&RenderRoutine::Setup2DTransform);
		}
		// Texture
		else if (SearchForString(t_Uniforms.at(i), "Texture"))
		{
			m_UniformSetupList.push_back(&RenderRoutine::SetupTextureUniforms);
		}
		// Material
		else if (t_Material != nullptr)
		{
			m_UniformSetupList.push_back(&RenderRoutine::SetupLightingUniforms);
			m_UniformSetupList.push_back(&RenderRoutine::SetupMaterialUniforms);
		}
	}

	CheckforGLErrors(__FILE__, __LINE__);
}