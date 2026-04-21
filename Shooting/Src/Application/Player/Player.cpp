#include "Player.h"

C_Player::C_Player()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_dirX = 3;
	m_dirY = 3;
}

C_Player::~C_Player()
{
	m_tex.Release();
}

void C_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= m_dirX;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += m_dirX;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += m_dirY;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= m_dirY;
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Player::Init()
{
	m_tex.Load("Player.png");
}
