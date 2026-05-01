#include "Score.h"

void C_Score::Draw()
{
    std::string score = std::to_string(m_score);

    float x = m_pos.x;
    float y = m_pos.y;

    int digitWidth = 16;   // 数字1桁の幅
    int digitHeight = 32;  // 数字の高さ
    int spacing = 5;       // ← ここを変えると間隔が変わる

    if(m_scoreFlg)
    {
        for (int i = 0; i < score.size(); i++)
        {
            int num = score[i] - '0'; // 文字 → 数字

            // 数字1つ分の切り取り範囲
            Math::Rectangle rect = { num * digitWidth, 0, digitWidth, digitHeight};
            Math::Color color = { 1.0f,1.0f,1.0f,m_alpha };

            // ★ 桁の間隔を追加
            Math::Matrix trans = Math::Matrix::CreateTranslation(x + i * (digitWidth + spacing), y, 0);

            SHADER.m_spriteShader.SetMatrix(trans);

            // 描画
            SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);
        }
    }

}

void C_Score::Update()
{
    m_alpha = (float)m_scoreTimer / m_timerReset;

    if (m_scoreFlg)
    {
        m_pos.y += m_upSpeed;
        m_scoreTimer--;

        if (m_scoreTimer <= m_timerLimit)
        {
            m_scoreFlg = false;
            m_scoreTimer = m_timerReset;
            m_alpha = m_alphaReset;
        }
    }

    UiUpdate();

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Score::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_tex.Load("Texture/Score/Suuji.png");
	m_score = 0;
    m_scoreTimer = 90;
    m_timerLimit = 0;
    m_timerReset = 90;
    m_alpha = 1.0f;
    m_alphaReset = 1.0f;
    m_upSpeed = 2.0f;
    m_scoreFlg = false;

    UiInit();

}

void C_Score::UiDraw(int _totalScore)
{
    char buf[16];
    sprintf_s(buf, "%08d", _totalScore); // 8桁でゼロ埋め（000000）
    std::string scoreStr = buf;
    // ------------------------------------------

    int digitWidth = 16;
    int spacing = 5;

    // 1桁ずつ描画
    for (int i = 0; i < (int)scoreStr.size(); i++) {
        int num = scoreStr[i] - '0';
        Math::Rectangle rect = { num * digitWidth, 0, digitWidth, 32 };
        Math::Color color = { 1.0f, 1.0f, 1.0f, m_uiAlpha };

        // 合計スコア用の行列計算
        m_uiTransMat = Math::Matrix::CreateTranslation(m_uiPos.x + i * (digitWidth + spacing),m_uiPos.y, 0 );

        // ※ m_uiMat に m_uiTransMat (または Scale * Trans) を代入する処理を忘れずに！
        m_uiMat = m_uiScaleMat * m_uiTransMat;

        // シェーダーにセットして描画
        SHADER.m_spriteShader.SetMatrix(m_uiMat);
        SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);
    }
}

void C_Score::UiUpdate()
{
    // 行列の初期化 (スケールなど)
    m_uiScaleMat = Math::Matrix::CreateScale(m_uiSize.x, m_uiSize.y, 0);
}

void C_Score::UiInit()
{
    // 合計スコアUIの初期設定
    m_uiPos = { 460.0f, 320.0f };
    m_uiSize = { 1.0f,1.0f };
    m_uiAlpha = 1.0f;
}
