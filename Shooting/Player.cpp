#include "Application/Player/Player.h"
#include "Application/GameScene/GameScene.h"

C_Player::C_Player()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_dirX = 7;
	m_dirY = 3;
	
	m_screenRight = 640;
	m_screenLeft = -640;
	m_screenTop = 360;
	m_screenDown = -360;
	m_hp = 10;
	m_alpha = 1.0f;
	m_delet = 0.0f;
	m_alphaReset = 1.0f;

	m_aliveFlg = true;
	m_hitFlg = false;
}

C_Player::~C_Player()
{
	m_tex.Release();
}

void C_Player::Draw()
{
	if (!m_aliveFlg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64),m_alpha);
}

void C_Player::Update()
{
	//プレイヤー移動処理
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

	//画面端当たり判定
	if (m_pos.x > m_screenRight - 32)
	{
		m_pos.x = m_screenRight - 32;
	}

	if(m_pos.x < m_screenLeft + 32)
	{
		m_pos.x = m_screenLeft + 32;
	}

	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_aliveFlg = false;
	}

	if (m_hitFlg)
	{
		m_alpha += m_delet;

		if (m_alpha <= 0.3f)
		{
			m_alpha = 0.3f;
		    m_delet = 0.03f;
		}
		else if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
			m_delet -= 0.03f;
		}

	}
	else
	{
		m_alpha = m_alphaReset;
	}


	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");
}
