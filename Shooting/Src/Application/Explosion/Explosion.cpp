#include "Explosion.h"

void C_Explosion::Draw()
{
	if(m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle((int)m_anime * 48, 48, 48, 48), 1.0f);
	}
}

void C_Explosion::Update()
{
	if (m_aliveFlg)
	{
		m_anime+= m_animeSpeed;

		if (m_anime >= m_maxAnimeFrame)
		{
			m_aliveFlg = false;
			m_anime = 0.0f;
		}

	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Explosion::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_anime = 0.0f;
	m_aliveFlg = false;
	m_tex.Load("Texture/Explosion/Explosion.png");;
}
