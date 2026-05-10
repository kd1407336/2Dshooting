#include "GameScreen.h"

void C_GameScreen::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 940, 1080), 1.0f);
}

void C_GameScreen::Update()
{
	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_GameScreen::Init()
{
	m_pos = { 480,0 };
	m_size = { 3.0f,2.5f };
	m_tex.Load("Texture/GameScreen/Screen.png");
}
