#include "GameScreen.h"

void C_GameScreen::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 320, 320), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_screen1Mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 320, 320), 1.0f);
}

void C_GameScreen::Update()
{
	m_pos.y -= 1;

	if (m_pos.y <= -720)
	{
		m_pos.y = 0;
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;

	m_screen1Trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y + 720, 0);
	m_screen1Scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_screen1Mat = m_screen1Scale * m_screen1Trans;
}

void C_GameScreen::Init()
{
	m_pos = { 0,0 };
	m_size = { 4.0f,2.5f };
	m_tex.Load("Texture/GameScreen/Screen.png");
}
