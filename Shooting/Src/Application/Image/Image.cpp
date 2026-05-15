#include "Image.h"

void C_Image::Draw()
{
	if (!m_aliveFlg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), m_alpha);
}

void C_Image::Update()
{
	if (!m_aliveFlg)return;


	// アルファ値を更新
	m_alpha += m_alphaSpeed;

	// 最小値（0.0fなど）以下になったら、増やす方向に反転
	if (m_alpha <= m_alphaMin)
	{
		m_alpha = m_alphaMin;
		m_alphaSpeed *= -1.0f; // ★ -1.0f で向きだけ変える
	}
	// 最大値（1.0fなど）以上になったら、減らす方向に反転
	else if (m_alpha >= m_alphaMax)
	{
		m_alpha = m_alphaMax;
		m_alphaSpeed *= -1.0f; // ★ -1.0f で向きだけ変える
	}


	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Image::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };

	m_alpha = 0.5f;
	m_alphaSpeed = 0.01f;
	m_alphaMin = 0.2f;
	m_alphaMax = 0.5f;
	m_alphaReset = 1.0f;
	m_aliveFlg = false;

	m_tex.Load("Texture/Boss/Red.png");
}

