#include "BossEnemy.h"
#include "Application/EnemyBullet/BossBullet.h"


void C_BossEnemy::Draw()
{
	if (m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
	}

    HpDraw();

}

void C_BossEnemy::Update()
{

    if (!m_aliveFlg) return;

    switch (m_state) {
    case BossState::Appear:
        // --- 登場シーン：上から下へ ---
        m_pos.y -= 3.0f;

        if (m_pos.y <= 280) {
            m_pos.y = 280;
            m_state = BossState::Move; // 指定位置に来たら「移動状態」へ
        }
        break;

    case BossState::Move:

        // タイマーの進む速さ（0.02f～0.05f くらいで調整してください）
        m_moveTimer += 0.015f;

        // --- 指定範囲（280 ～ -580）での移動 ---
        float centerX = -150.0f; // 移動範囲の中心
        float amplitude = 360.0f; // 中心からの振れ幅

        // sinf(-1.0～1.0) を使って範囲内を往復させる
        m_pos.x = centerX + sinf(m_moveTimer) * amplitude;

        // --- 上下のふわふわ（お好みで） ---
        m_pos.y = 280 + sinf(m_moveTimer * 0.5f) * 15.0f;
        break;
    }

    HpUpdate();

    

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_BossEnemy::Init()
{
	m_pos = { 0,460 };
	m_size = { 3.0f,3.0f };
    m_shotTimer = 60; // ← これを追加（出現してから1秒後に発射開始）
    m_hp = 100;
	m_tex.Load("Texture/Enemy/Enemy.png");
	m_aliveFlg = false;
	m_hitFlg = false;

    HpInit();
   
}

void C_BossEnemy::HpDraw()
{
    if(m_aliveFlg)
    {
        //HP（黒）
        SHADER.m_spriteShader.SetMatrix(m_hpBerMat);
        Math::Rectangle hpBerRect = { 0,0,271,21 };
        Math::Color hpBerColor = { 0.0f,0.0f,0.0f,1.0f };
        SHADER.m_spriteShader.DrawTex(&m_hpTex, 0, 0, &hpBerRect, &hpBerColor);

        // --- 1. 背景または削れている部分（赤）を先に描く ---
        SHADER.m_spriteShader.SetMatrix(m_hpDrawMat); // m_hpDraw(遅れて減る方)を使用
        Math::Rectangle rect = { 0, 0, 271, 21 };
        Math::Color redColor = { 1.0f, 0.0f, 0.0f, 1.0f }; // 赤色
        SHADER.m_spriteShader.DrawTex(&m_hpTex, 0, 0, &rect, &redColor);

        // --- 2. 現在のHP（緑）を上に重ねて描く ---
        SHADER.m_spriteShader.SetMatrix(m_hpMat); // m_hp(すぐ減る方)を使用
        Math::Color greenColor = { 0.0f, 1.0f, 0.0f, 1.0f }; // 緑色
        SHADER.m_spriteShader.DrawTex(&m_hpTex, 0, 0, &rect, &greenColor);
    }
}


void C_BossEnemy::HpUpdate()
{
    // --- 1. HPゲージが徐々に追いつく処理（赤ゲージの更新） ---
    if (m_hpDraw > m_hp)
    {
        // ボスはHPが多いので、減少スピードをプレイヤー（0.05f）より少し速め（0.3f）に設定
        m_hpDraw -= 0.3f;

        if (m_hpDraw < m_hp)
        {
            m_hpDraw = m_hp;
        }
    }

    // --- 2. 共通の設定値 ---
    const float baseHalfWidth = 135.5f; // 元の画像幅(271)の半分
    const float scaleX = 1.5f;          // 横幅：1.5倍（大きく）
    const float scaleY = 1.2f;          // 縦幅：1.2倍
    const float currentHalfWidth = baseHalfWidth * scaleX; // スケール後の幅の半分（203.25f）

    // --- 3. 赤いバー（追いかける方：m_hpDraw）の行列計算 ---
    float redRate = m_hpDraw / m_hpMax;
    if (redRate < 0.0f) redRate = 0.0f;
    if (redRate > 1.0f) redRate = 1.0f;

    // スケール行列：横は割合×1.5、縦は1.2
    Math::Matrix redScaleMat = Math::Matrix::CreateScale(redRate * scaleX, scaleY, 1.0f);

    // 左端を固定するための移動量計算
    float redOffsetX = currentHalfWidth * (1.0f - redRate);
    Math::Matrix redTransMat = Math::Matrix::CreateTranslation(m_hpPos.x - redOffsetX, m_hpPos.y, 0);

    m_hpDrawMat = redScaleMat * redTransMat;


    // --- 4. 緑のバー（現在のHP：m_hp）の行列計算 ---
    float greenRate = m_hp / m_hpMax;
    if (greenRate < 0.0f) greenRate = 0.0f;
    if (greenRate > 1.0f) greenRate = 1.0f;

    // スケール行列
    Math::Matrix greenScaleMat = Math::Matrix::CreateScale(greenRate * scaleX, scaleY, 1.0f);

    // 左端を固定するための移動量計算
    float greenOffsetX = currentHalfWidth * (1.0f - greenRate);
    Math::Matrix greenTransMat = Math::Matrix::CreateTranslation(m_hpPos.x - greenOffsetX, m_hpPos.y, 0);

    m_hpMat = greenScaleMat * greenTransMat;


    // --- 5. 黒い枠（背景：m_hpBerMat）の行列計算 ---
    // 枠は常に最大幅（1.5倍）で表示する
    Math::Matrix berScaleMat = Math::Matrix::CreateScale(scaleX, scaleY, 1.0f);
    Math::Matrix berTransMat = Math::Matrix::CreateTranslation(m_hpBerPos.x, m_hpBerPos.y, 0);

    m_hpBerMat = berScaleMat * berTransMat;
}


void C_BossEnemy::HpInit()
{
    m_hpMax = 50.0f; // 例：プレイヤーより多め
    m_hp = m_hpMax;
    m_hpDraw = m_hpMax;

    m_hpPos = { 0,320 };
    m_hpSize = { 1.5f,1.2f };


    m_hpBerPos = { 0,320 };
    m_hpBerSize = { 1.5f,1.2f };

    m_hpTex.Load("Texture/HpBer/HpBer.png");

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
            // --- 前方（下向き）だけに限定して撃ち分ける ---
            // m_currentShotAngle を使って 220度 ～ 320度 の間を往復させる例
            m_currentShotAngle += 15.0f;

            // 指定の角度を超えたら反対側に戻す（これで後ろに飛ばない）
            if (m_currentShotAngle > 320.0f || m_currentShotAngle < 220.0f) {
                m_currentShotAngle = 220.0f;
            }

            float rad = m_currentShotAngle * (3.14159f / 180.0f);

            // 弾の速度（4.0f）
            Math::Vector2 v = { cosf(rad) * 4.0f, sinf(rad) * 4.0f };

            // 発射位置（ボスの中心 m_pos から少しずらす）
            Math::Vector2 offset = { cosf(rad) * 40.0f, sinf(rad) * 40.0f };

            b->SetPos(m_pos + offset);
            b->SetVelocity(v);
            b->SetAliveFlg(true);

            m_shotTimer = 10;
            return;
        }
    }
}

void C_BossEnemy::Shoot3WayStep(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    // 1. タイマー更新
    m_shotTimer--;
    if (m_shotTimer > 0) return;

    // --- 調整用パラメータ ---
    const int nextShotDelay = 15; // 次に「3発同時」に撃つまでの待ち時間
    // ----------------------

    // 同時に出す3つの方向（速度ベクトル）を定義
 // プラスが上、マイナスが下なので、Yをマイナスに設定
    Math::Vector2 vels[] = {
        { 0.0f, -4.0f}, // 中央（真下）
        { 2.0f, -4.0f}, // 右斜め下
        {-2.0f, -4.0f}  // 左斜め下
    };

    int fireCount = 0; // 今回発射した数を数える

    for (auto& b : list)
    {
        if (!b->GetAliveFlg())
        {
            // 弾をセット
            b->SetPos(m_pos);
            b->SetVelocity(vels[fireCount]); // 0:中央、1:右、2:左 の順で適用
            b->SetAliveFlg(true);

            fireCount++;

            // 3発セットし終わったらループを抜ける
            if (fireCount >= 3) break;
        }
    }

    // 3発撃った（またはリストがいっぱいになった）らタイマーをセット
    if (fireCount > 0)
    {
        m_shotTimer = nextShotDelay;
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

void C_BossEnemy::Damage()
{
    m_hp = m_hp - 1;
}

