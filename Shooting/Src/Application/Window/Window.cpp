#include "Window.h"

void C_Window::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 940, 1080), 1.0f);
}

void C_Window::Update()
{
	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Window::Init()
{
	m_pos = { 475,0 };
	m_size = { 0.35f,0.67f };
	m_tex.Load("Texture/Window/Window.png");
}
