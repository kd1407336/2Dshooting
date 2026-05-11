#include "ResultLogo.h"

void C_ResultLogo::Init(bool isClear)
{
    m_isClear = isClear;
    m_aliveFlg = true;

    if (m_isClear)
    {
        // --- クリアロゴの設定 ---
        m_clearTex.Load("Texture/Game/GameClear.png");
        m_clearPos = { 10.0f, 200.0f }; // 画面中央上部
        m_clearSize = { 1.8f, 1.8f };
        m_clearAlpha = 0.0f;
        m_clearAlphaMax = 1.0f;
        m_clearAlphaSpeed = 0.02f;
    }
    else
    {
        // --- オーバーロゴの設定 ---
        m_overTex.Load("Texture/Game/GameOver.png");
        m_overPos = { 0.0f, 200.0f }; // 同じ位置
        m_overSize = { 1.5f, 1.5f };
        m_overAlpha = 0.0f;
        m_overAlphaMax = 1.0f;
        m_overAlphaSpeed = 0.02f;
    }
}

void C_ResultLogo::Update()
{
    if (!m_aliveFlg) return;

    if (m_isClear)
    {
        // --- クリア用のフェード更新 ---
        m_clearAlpha += m_clearAlphaSpeed;
        if (m_clearAlpha >= m_clearAlphaMax)
        {
            m_clearAlpha = m_clearAlphaMax;
        }

        // 行列計算
        m_clearScaleMat = Math::Matrix::CreateScale(m_clearSize.x, m_clearSize.y, 1.0f);
        m_clearTransMat = Math::Matrix::CreateTranslation(m_clearPos.x, m_clearPos.y, 0);
        m_clearMat = m_clearScaleMat * m_clearTransMat;
    }
    else
    {
        // --- オーバー用のフェード更新 ---
        m_overAlpha += m_overAlphaSpeed;
        if (m_overAlpha >= m_overAlphaMax)
        {
            m_overAlpha = m_overAlphaMax;
        }

        // 行列計算
        m_overScaleMat = Math::Matrix::CreateScale(m_overSize.x, m_overSize.y, 1.0f);
        m_overTransMat = Math::Matrix::CreateTranslation(m_overPos.x, m_overPos.y, 0);
        m_overMat = m_overScaleMat * m_overTransMat;
    }
}

void C_ResultLogo::Draw()
{
    if (!m_aliveFlg) return;

    if (m_isClear)
    {
        SHADER.m_spriteShader.SetMatrix(m_clearMat);
        Math::Rectangle rect = { 0, 0, 332, 47 };
        Math::Color color = { 1.0f, 1.0f, 1.0f, m_clearAlpha }; // クリア用α
        SHADER.m_spriteShader.DrawTex(&m_clearTex, 0, 0, &rect, &color);
    }
    else
    {
        SHADER.m_spriteShader.SetMatrix(m_overMat);
        Math::Rectangle rect = { 0, 0, 373,60 };
        Math::Color color = { 1.0f, 1.0f, 1.0f, m_overAlpha };  // オーバー用α
        SHADER.m_spriteShader.DrawTex(&m_overTex, 0, 0, &rect, &color);
    }
}