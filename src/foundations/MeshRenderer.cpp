#include "MeshRenderer.h"
#include "Foundations.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "game/Player.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>

using namespace Foundation;

void MeshRenderer::OnInit()
{
	m_angle = 0;

	m_shader = std::make_shared<Shader>("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");

	SetMesh(GetFoundation()->GetComponent<Snake>()->GetModel());
	SetMaterial(GetFoundation()->GetComponent<Snake>()->GetTexture());

	m_shader->SetUniform("in_Projection", GetFoundation()->GetComponent<Camera>()->GetProjection());
}

void MeshRenderer::OnUpdate(float _deltaTime)
{
	m_shader->SetUniform("in_View", GetFoundation()->GetComponent<Camera>()->GetView());

	m_angle += 100.0f * _deltaTime;
}

void MeshRenderer::OnDisplay()
{
	glm::mat4 cube(1.0f);

	glm::vec3 cubePos = GetFoundation()->GetComponent<Snake>()->GetPlayerPosition();
	cube = glm::translate(cube, cubePos);

	m_shader->SetUniform("in_Model", cube);
	m_shader->SetUniform("in_Texture", m_currentTexture.lock());

	m_shader->Draw(*m_currentMesh.lock());
}

void MeshRenderer::SetMesh(std::weak_ptr<VertexArray> _mesh)
{
	m_currentMesh = _mesh;
}

void MeshRenderer::SetMaterial(std::weak_ptr<Texture> _texture)
{
	m_currentTexture = _texture;
}

std::shared_ptr<VertexArray> MeshRenderer::GetMesh()
{
	return m_currentMesh.lock();
}

std::shared_ptr<Texture> MeshRenderer::GetMaterial()
{
	return m_currentTexture.lock();
}