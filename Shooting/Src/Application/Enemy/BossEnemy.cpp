#include "BossEnemy.h"
#include "Application/EnemyBullet/BossBullet.h"


void C_BossEnemy::Draw()
{

    if (!m_aliveFlg) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 128, 128), 1.0f);

    HpDraw();
}

void C_BossEnemy::Update()
{

    HpUpdate();

    m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
    m_mat = m_scale * m_trans;

    if (!m_aliveFlg) return;

    switch (m_state) {
    case BossState::Appear:
        // --- 登場シーン：上から下へ ---
        m_pos.y -= 3.0f;

        if (m_pos.y <= 170) {
            m_pos.y =170;
            m_state = BossState::Move; // 指定位置に来たら「移動状態」へ
        }
        break;

    case BossState::Move:

        // タイマーの進む速さ（0.02f～0.05f くらいで調整してください）
        m_moveTimer += 0.01f;

        // --- 指定範囲（280 ～ -580）での移動 ---
        float centerX = -150.0f; // 移動範囲の中心
        float amplitude = 360.0f; // 中心からの振れ幅

        // sinf(-1.0～1.0) を使って範囲内を往復させる
        m_pos.x = centerX + sinf(m_moveTimer) * amplitude;

        // --- 上下のふわふわ（お好みで） ---
        m_pos.y = 160 + sinf(m_moveTimer * 0.5f) * 15.0f;
        break;
    }
}

void C_BossEnemy::Init()
{
	m_pos = { -110,460 };
	m_size = { 2.8f,2.8f };
    m_shotTimer = 60; // ← これを追加（出現してから1秒後に発射開始）
    m_hp = 200;
	m_tex.Load("Texture/Enemy/BossEnemy.png");
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


        // BOSSロゴの描画
        Math::Rectangle bossRect = { 0, 0, 102, 41 };
        Math::Color color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SHADER.m_spriteShader.SetMatrix(m_bossLogoMat);
        SHADER.m_spriteShader.DrawTex(&m_bossLogoTex, 0, 0, &bossRect, &color);

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


    // 行列の計算を分離して行う
    m_bossLogoScaleMat = Math::Matrix::CreateScale(m_bossLogoSize.x, m_bossLogoSize.y, 1.0f);
    m_bossLogoTransMat = Math::Matrix::CreateTranslation(m_bossLogoPos.x, m_bossLogoPos.y, 0.0f);

    // 合成 (S * T)
    m_bossLogoMat = m_bossLogoScaleMat * m_bossLogoTransMat;

}


void C_BossEnemy::HpInit()
{
    m_hpMax = 200.0f; // 例：プレイヤーより多め
    m_hp = m_hpMax;
    m_hpDraw = m_hpMax;

    m_hpPos = { -100,320 };
    m_hpSize = { 1.5f,1.2f };


    m_hpBerPos = { -100,320 };
    m_hpBerSize = { 1.5f,1.2f };

    m_hpTex.Load("Texture/HpBer/HpBer.png");


    m_bossLogoTex.Load("Texture/Boss/Boss.png");

    // HPバーの座標(m_hpPos)を基準に、左(-220)・少し上(10)に配置
    m_bossLogoPos = { -370,320 };
    m_bossLogoSize = { 1.2f, 1.2f }; // 少し大きめに設定

}

void C_BossEnemy::Shoot(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    if (!m_aliveFlg) return;

    ShootCircleStep(list);

}


// プレイヤーのポインタや座標を引数に追加するか、内部で取得する
void C_BossEnemy::ShootAimNWay(std::vector<std::unique_ptr<C_BossBullet>>& list, Math::Vector2 playerPos)
{
    m_shotTimer--;
    if (m_shotTimer > 0) return;

    // --- 改造ポイント：自機への角度を計算 ---
    Math::Vector2 diff = playerPos - m_pos;
    float baseAngleRad = atan2f(diff.y, diff.x);
    float baseAngle = baseAngleRad * (180.0f / 3.14159f);

    int wayCount = 5; // 奇数にすると中央の弾が自機に真っ直ぐ飛んできます
    float spread = 15.0f; // 狙い撃ちなので少し狭めるのがコツ

    for (int i = 0; i < wayCount; i++)
    {
        float angleOffset = (i - (wayCount - 1) / 2.0f) * spread;
        float finalRad = (baseAngle + angleOffset) * (3.14159f / 180.0f);

        for (auto& b : list)
        {
            if (!b->GetAliveFlg())
            {
                Math::Vector2 v = { cosf(finalRad) * 5.0f, sinf(finalRad) * 5.0f };
                b->SetPos(m_pos + Math::Vector2(0, -50.0f));
                b->SetVelocity(v);
                b->SetAliveFlg(true);
                break;
            }
        }
    }
    m_shotTimer = 45;
}


void C_BossEnemy::ShootCircleStep(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    m_shotTimer--;
    if (m_shotTimer > 0) return;

    // --- 調整用パラメータ ---
    float angleStep = 40.0f;     // ★弾と弾の間隔（ここを自由に変えられます）
    float startAngle = 0.0f;     // 開始角度（回転させたい場合はここを増やす）
    float bulletSpeed = 4.0f;    // 弾の速さ

    // 360度を angleStep で割って、発射する弾の数を計算する
    // 例：30度間隔なら 360 / 30 = 12発
    int wayCount = static_cast<int>(360.0f / angleStep);

    for (int i = 0; i < wayCount; i++)
    {
        // 0度から順番に angleStep ずつずらしていく
        float currentAngle = startAngle + (i * angleStep);
        float finalRad = currentAngle * (3.14159f / 180.0f);

        // 未使用の弾を探して発射
        for (auto& b : list)
        {
            if (!b->GetAliveFlg())
            {
                // ベクトル計算
                Math::Vector2 v = { cosf(finalRad) * bulletSpeed, sinf(finalRad) * bulletSpeed };

                // 発射位置（ボスの中心）
                b->SetPos(m_pos + Math::Vector2 (-5,-130));
                b->SetVelocity(v);
                b->SetAliveFlg(true);
                break;
            }
        }
    }

    m_shotTimer = 15; // 次の発射までの間隔
}


void C_BossEnemy::Shoot3WayStep(std::vector<std::unique_ptr<C_BossBullet>>& list)
{
    // 1. タイマー更新
    m_shotTimer--;
    if (m_shotTimer > 0) return;

    // --- 調整用パラメータ ---
    const int nextShotDelay = 45
        
        
        
        ; // 次に「3発同時」に撃つまでの待ち時間
    // ----------------------

    // 同時に出す3つの方向（速度ベクトル）を定義
 // プラスが上、マイナスが下なので、Yをマイナスに設定
    Math::Vector2 vels[] = {
        { 0.0f, -5.0f}, // 中央（真下）
        { 2.0f, -5.0f}, // 右斜め下
        {-2.0f, -5.0f}  // 左斜め下
    };

    int fireCount = 0; // 今回発射した数を数える

    for (auto& b : list)
    {
        if (!b->GetAliveFlg())
        {
            // 弾をセット
            b->SetPos(m_pos + Math::Vector2(0, -80.0f));
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

