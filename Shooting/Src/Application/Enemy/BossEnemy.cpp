#include "BossEnemy.h"
#include "Application/EnemyBullet/BossBullet.h"


void C_BossEnemy::Draw()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
	}
}

void C_BossEnemy::Update()
{

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_BossEnemy::Init()
{
	m_pos = { 0,0 };
	m_size = { 3.0f,3.0f };
    m_shotTimer = 60; // ← これを追加（出現してから1秒後に発射開始）
	m_tex.Load("Texture/Enemy/Player.png");
	m_aliveFlg = false;
	m_hitFlg = false;
}

void C_BossEnemy::Shoot(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    if (!m_aliveFlg) return;

    ShootCircleStep(list);

}

void C_BossEnemy::ShootCircleStep(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    m_shotTimer--;
    if (m_shotTimer > 0) return;

    for (auto& b : list)
    {
        if (!b->GetAliveFlg())
        {
            float rad = m_currentShotAngle * (3.14159f / 180.0f);
            Math::Vector2 v = { cosf(rad) * 4.0f, sinf(rad) * 4.0f };

            // ★改良：ボスの中心から少し離れた位置から発射する
            // これにより、ボスのグラフィックと重なって見づらくなるのを防ぎます
            Math::Vector2 offset = { cosf(rad) * 40.0f, sinf(rad) * 40.0f };
            b->SetPos(m_pos + offset);

            b->SetVelocity(v);
            b->SetAliveFlg(true);

            m_currentShotAngle += 20.0f; // 角度をズラす

            m_shotTimer = 10; // 次の弾までの間隔（ここを調整）

            return; // ★重要：1発撃ったらこの関数の処理を完全に抜ける！
        }
    }
}
void C_BossEnemy::Shoot3WayStep(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    // タイマー更新
    m_shotTimer--;
    if (m_shotTimer > 0) return;

    // 速度パターンの定義
    Math::Vector2 vels[] = { {-2.0f, -4.0f}, {0.0f, -4.0f}, {2.0f, -4.0f} };

    for (auto& b : list)
    {
        if (!b->GetAliveFlg())
        {
            // 発射処理
            b->SetPos(m_pos);
            b->SetVelocity(vels[m_wayCount]);
            b->SetAliveFlg(true);

            m_wayCount++; // 何発目かをカウントアップ

            // --- ここがリセットの肝 ---
            if (m_wayCount >= 3)
            {
                // 3発撃ち終わったら、次のセットまで長く待つ（例：120フレーム＝2秒）
                m_shotTimer = 120;
                m_wayCount = 0; // カウントを0に戻す
            }
            else
            {
                // まだ途中（1発目、2発目）なら、短い間隔で次を撃つ（例：10フレーム）
                m_shotTimer = 10;
            }
            // ------------------------

            return; // 1発撃ったので終了
        }
    }
}
void C_BossEnemy::ShootCircle(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    const int num = 16; // 16方向に撃ち出す
    int shootCount = 0;

    for (int i = 0; i < num; i++) {
        // 360度を等分してラジアンに変換
        float angle = (360.0f / num) * i;
        float rad = angle * (3.14159f / 180.0f);

        // 単位円から速度を計算（速度4.0f）
        Math::Vector2 v = { cosf(rad) * 4.0f, sinf(rad) * 4.0f };

        // リストから空いている弾を探す
        for (auto& b : list) {
            if (!b->GetAliveFlg()) {
                b->SetPos(m_pos);
                b->SetVelocity(v);
                b->SetAliveFlg(true);
                shootCount++;
                break;
            }
        }
    }
}

