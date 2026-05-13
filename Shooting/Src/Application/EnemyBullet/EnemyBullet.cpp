#include "EnemyBullet.h"

void C_EnemyBullet::Draw()
{
	if (!m_aliveFlg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle((int)m_anime * 16, 16, 16, 16), 1.0f);
}

void C_EnemyBullet::Update()
{
	if (m_aliveFlg)
	{
		// セットされた速度（0, -5）を今の座標に足す
		m_pos += m_velocity;

		m_anime += m_animeSpeed;

		if (m_anime >= m_animeMax)
		{
			m_anime = m_animeMax;
			m_anime = m_animeReset;
		}

		// 画面端（下は-360ですが、余裕をもって-400）を超えたら消す
		if (m_pos.y  > 360 || m_pos.y < -400.0f)
		{
			m_aliveFlg = false;
		}

	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_EnemyBullet::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_anime = 0;
	m_animeSpeed = 0.1f;
	m_animeMax = 5.0f;
	m_animeReset = 0.0f;
	m_tex.Load("Texture/Bullet/EnemyBullet.png");
}
