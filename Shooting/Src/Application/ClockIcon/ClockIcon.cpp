#include "ClockIcon.h"

void C_ClockIcon::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 55, 60), m_alpha);
}

void C_ClockIcon::Update()
{
	if (m_aliveFlg)
	{
		if (m_isIncreasing) 
		{
			m_alpha += m_alphaSpeed;
			if (m_alpha >= m_alphaMax) 
			{
				m_alpha = m_alphaMax;
				m_isIncreasing = false; // 減少モードへ
			}
		}
		else {
			m_alpha -= m_alphaSpeed;
			if (m_alpha <= m_alphaMin)
			{
				m_alpha = m_alphaMin;
				m_isIncreasing = true; // 増加モードへ
			}
		}

	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_ClockIcon::Init()
{
	m_pos = { -190,60 };
	m_size = { 1.3f,1.3f };

	m_alpha = 1.0f;
	m_alphaSpeed = 0.02f;
	m_alphaMax = 1.0f;
	m_alphaMin = 0.2f;
	m_alphaReset = 1.0f;
	m_aliveFlg = false;
	m_isIncreasing = false;

	m_tex.Load("Texture/ClockIcon/ClockIcon.png");
}
