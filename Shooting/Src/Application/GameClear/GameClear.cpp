#include "GameClear.h"

void C_GameClear::Draw()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 332, 47), m_alpha);
	}
}

void C_GameClear::Update()
{
	if (m_aliveFlg)
	{
		m_alpha += m_alphaSpeed;

		if (m_alpha >= m_alphaMax)
		{
			m_alpha = m_alphaMax;
		}
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_GameClear::Init()
{
	m_pos = { -100,250 };
	m_size = { 1.5f,1.5f };
	m_alpha = 0.0f;
	m_alphaMax = 1.0f;
	m_alphaSpeed = 0.01f;
	m_tex.Load("Texture/Game/GameClear.png");
	m_aliveFlg = false;
}
