#include "HomeIcon.h"

void C_HomeIcon::Draw()
{
	Math::Rectangle rect = { 0,0,128,128 };
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0,0,&rect,&color);
}

void C_HomeIcon::Update()
{
	if (m_iconFlg)
	{
		m_size = { 0.9f,0.9f };
	}
	else
	{
		m_size = { m_sizeReset.x,m_sizeReset.y };
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_HomeIcon::Init()
{
	m_pos = { 580,280 };
	m_size = { 0.7f,0.7f };
	m_sizeReset = { 0.7f,0.7f };
	m_tex.Load("Texture/HomeIcon/HomeIcon.png");
	m_iconFlg = false;
}
