#include "Level.h"

void C_Level::Level1Draw()
{
	if (!m_level1Flg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 69, 50), m_alpha1);
}

void C_Level::Level1Update()
{
	if (m_level2Flg)
	{
		m_alpha1 -= m_fadeSpeed;

		if (m_alpha1 <= 0.0f)
		{
			m_alpha1 = 0.0f;
			m_level1Flg = false;
		}
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Level::Level1Init()
{
	m_pos = { 500,80 };
	m_size = { 1.7f,1.7f };
	m_alpha1 = 1.0f;
	m_fadeSpeed = 0.01f;
	m_tex.Load("Texture/Level/Level.png");
	m_level1Flg = true;
}

void C_Level::Level2Draw()
{
	if (!m_level2Flg)return;
	SHADER.m_spriteShader.SetMatrix(m_levelMat);
	SHADER.m_spriteShader.DrawTex(&m_levelTex, Math::Rectangle(0, 0, 69, 50), m_alpha2);
}

void C_Level::Level2Update()
{
	if (m_level2Flg)
	{
		m_alpha2 += m_fadeSpeed;

		if (m_alpha2 >= 1.0f) { m_alpha2 = 1.0f; }
	}

	m_levelTrans = Math::Matrix::CreateTranslation(m_levelPos.x, m_levelPos.y, 0);
	m_levelScale = Math::Matrix::CreateScale(m_levelSize.x, m_levelSize.y, 0);
	m_levelMat = m_levelScale * m_levelTrans;
}

void C_Level::Level2Init()
{
	m_levelPos = { 510,75 };
	m_levelSize = { 2.0f,2.0f };
	m_alpha2 = 0.0f;
	m_levelTex.Load("Texture/Level/Level2.png");
	m_level2Flg = false;
}
