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
	m_hpMax = 10;
	m_hpDraw = 10.0f;

	m_alpha = 1.0f;
	m_alphaMin = 0.3f;
	m_alphaMax = 1.0f;
	m_alphaReset = 1.0f;
	m_delet = 0.0f;

	m_charaRadius = 32;
	
	m_aliveFlg = true;
	m_hitFlg = false;
	m_hitOnFlg = false;
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

	HpDraw();
	BulletDraw();

}

void C_Player::Update()
{
	
	Action();
	HpUpdate();
	BulletUpdate();

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");
	HpInit();
	BulletInit();
}

void C_Player::Action()
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
	if (m_pos.x > m_screenRight - m_charaRadius)
	{
		m_pos.x = m_screenRight - m_charaRadius;
	}

	if (m_pos.x < m_screenLeft + m_charaRadius)
	{
		m_pos.x = m_screenLeft + m_charaRadius;
	}

	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_aliveFlg = false;
	}

	if (m_hitFlg)
	{
		m_alpha += m_delet;

		if (m_alpha <= m_alphaMin)
		{
			m_alpha = m_alphaMin;
			m_delet = 0.05f;
		}
		else if (m_alpha >= m_alphaMax)
		{
			m_alpha = m_alphaMax;
			m_delet -= 0.05f;
		}

	}
	else
	{
		m_alpha = m_alphaReset;
	}
}

void C_Player::HpDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_hpMat);
	Math::Rectangle rect = { 0,0,271,21 };
	Math::Color hpColor = { 0.0f,1.0f,0.0f,1.0f };
	SHADER.m_spriteShader.DrawTex(&m_hpTex, 0, 0, &rect, &hpColor);
}

void C_Player::HpUpdate()
{
	//HPが徐々に減るようにする
	if (m_hpDraw > m_hp)
	{
		m_hpDraw -= 0.3f;

		if (m_hpDraw < m_hp)
		{
			m_hpDraw = m_hp;
		}

	}

	//HP割合を計算
	float HpRate = m_hpDraw / m_hpMax;
	if (HpRate < 0.0f) { HpRate = 0.0f; }
	else if (HpRate > 0.8f) { HpRate = 0.8f; }

	m_hpSize.x = HpRate;

	m_hpTrans = Math::Matrix::CreateTranslation(m_hpPos.x, m_hpPos.y, 0);
	m_hpScale = Math::Matrix::CreateScale(m_hpSize.x, m_hpSize.y, 0);
	m_hpMat = m_hpScale * m_hpTrans;
}

void C_Player::HpInit()
{
	m_hpPos = { -200,250 };
	m_hpSize = { 0.8f,1.0f };
	m_hpTex.Load("Texture/HpBer/HpBer.png");
}

void C_Player::BulletDraw()
{
	if(m_bulletFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_bulletMat);
		SHADER.m_spriteShader.DrawTex(&m_bulletTex, Math::Rectangle(0, 0, 16, 16), 1.0f);
	}
}

void C_Player::BulletUpdate()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_bulletFlg = true;
		m_bulletPos.x = m_pos.x;
		m_bulletPos.y = m_pos.y + 10;
		
	}

	if (m_bulletFlg)
	{
		m_bulletPos.y += 7;
	}

	if (m_bulletPos.y >= 390)
	{
		m_bulletFlg = false;
	}

	m_bulletTrans = Math::Matrix::CreateTranslation(m_bulletPos.x, m_bulletPos.y, 0);
	m_bulletScale = Math::Matrix::CreateScale(m_bulletSize.x, m_bulletSize.y ,0);
	m_bulletMat = m_bulletScale * m_bulletTrans;

}

void C_Player::BulletInit()
{
	m_bulletPos ={ 0,0 };
	m_bulletSize = { 1.0f,1.0f };
	m_bulletTex.Load("Texture/Bullet/Bullet.png");
	m_bulletFlg = false;
}
