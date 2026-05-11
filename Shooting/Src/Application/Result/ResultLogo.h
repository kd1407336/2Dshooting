#pragma once

class C_ResultLogo
{
public:
    void Init(bool isClear);
    void Update();
    void Draw();

private:
    // --- ① ゲームクリア用セット ---
    Math::Vector2 m_clearPos;
    Math::Vector2 m_clearSize;
    Math::Matrix  m_clearScaleMat; // 追加
    Math::Matrix  m_clearTransMat; // 追加
    Math::Matrix  m_clearMat;
    KdTexture     m_clearTex;
    float         m_clearAlpha;
    float         m_clearAlphaMax;   // 最大透明度
    float         m_clearAlphaSpeed; // フェード速度

    // --- ② ゲームオーバー用セット ---
    Math::Vector2 m_overPos;
    Math::Vector2 m_overSize;
    Math::Matrix  m_overScaleMat;  // 追加
    Math::Matrix  m_overTransMat;  // 追加
    Math::Matrix  m_overMat;
    KdTexture     m_overTex;
    float         m_overAlpha;
    float         m_overAlphaMax;    // 最大透明度
    float         m_overAlphaSpeed;  // フェード速度

    bool          m_isClear;
    bool          m_aliveFlg;
};