#include "BossBullet.h"

void C_BossBullet::Draw()
{
	if (!m_aliveFlg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 16, 16), 1.0f);
}

void C_BossBullet::Update()
{
	if (!m_aliveFlg) return;
	m_pos += m_velocity;
	
	if (m_pos.y > 400.0f || m_pos.y < -400.0f ||
		m_pos.x > 700.0f || m_pos.x < -700.0f)
	{
		m_aliveFlg = false;
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_BossBullet::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.5f,1.5f };
	m_tex.Load("Texture/Bullet/Bullet.png");

}
