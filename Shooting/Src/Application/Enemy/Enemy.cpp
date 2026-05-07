#include "Enemy.h"
#include "Application/EnemyBullet/EnemyBullet.h"

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

	m_pos.y -= 2.0f;

	if (m_pos.y <= -360)
	{
		m_pos.y = 390;
	}

	if (m_shotTimer > 0) 
	{
		m_shotTimer--;
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Enemy::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_shotTimer = 0;
	m_tex.Load("Texture/Enemy/Player.png");
	m_aliveFlg = true;
	m_hitFlg = false;
}

void C_Enemy::Action()
{
	
}

void C_Enemy::Shoot(std::vector<std::unique_ptr<C_EnemyBullet>>& bulletList)
{
	if (!m_aliveFlg) return;
	if (m_shotTimer > 0) return;

	for (auto& b : bulletList)
	{
		if (!b->GetAliveFlg())
		{
			b->SetPos({ m_pos.x, m_pos.y - 32.0f });

			// --- 速度をランダムにする計算 ---
			// 例：基本の速さ 3.0 に、0.0〜4.0 のランダム値を足す（合計 3.0〜7.0）
			float randomSpeed = 3.0f + static_cast<float>(rand() % 41) / 10.0f;

			// 下方向に飛ぶのでマイナスにする
			b->SetVelocity({ 0.0f, -randomSpeed });
			// ------------------------------

			b->SetAliveFlg(true);
			m_shotTimer = 180;
			return;
		}
	}
}

void C_Enemy::Reset(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_shotTimer = 60 + (rand() % 120);
	m_aliveFlg = true;
}
