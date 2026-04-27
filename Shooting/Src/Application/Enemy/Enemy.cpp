#include "Enemy.h"

void C_Enemy::Draw()
{
	if(m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
	}
}

void C_Enemy::Update()
{
	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Enemy::Init()
{
	m_pos = { 0,100 };
	m_size = { 1.0f,1.0f };
	m_tex.Load("Texture/Enemy/Player.png");
	m_aliveFlg = true;
}
