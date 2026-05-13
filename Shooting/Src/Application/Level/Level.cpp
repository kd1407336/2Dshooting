#include "Level.h"

void C_Level::Level1Draw()
{
	if (!m_level1Flg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 140, 50), m_alpha1);
}

void C_Level::Level1Update()
{
	if (m_level2Flg)
	{
		m_alpha1 -= m_fadeSpeed;

		if (m_alpha1 <= 0.0f)
		{
			m_alpha1 = 0.0f;
			m_level1Flg = false;
		}
	}

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Level::Level1Init()
{
	m_pos = { 397,-65 };
	m_size = { 1.0f,1.0f };
	m_alpha1 = 1.0f;
	m_fadeSpeed = 0.01f;
	m_tex.Load("Texture/Level/Level1.png");
	m_level1Flg = true;
}

void C_Level::Level2Draw()
{
	if (!m_level2Flg)return;
	SHADER.m_spriteShader.SetMatrix(m_levelMat);
	SHADER.m_spriteShader.DrawTex(&m_levelTex, Math::Rectangle(0, 0, 140, 50), m_alpha2);
}

void C_Level::Level2Update()
{
	if (!m_level2Flg)
	{
		m_alpha2 += m_fadeSpeed;

		if (m_alpha2 >= 1.0f) { m_alpha2 = 1.0f; }
	}

	if (m_level3Flg)
	{
        m_alpha2 -= m_alpha2Speed;

        if (m_alpha2 <= 0.0f)
        {
            m_alpha2 = 0.0f;
            m_level2Flg = false;
        }
	}


	m_levelTrans = Math::Matrix::CreateTranslation(m_levelPos.x, m_levelPos.y, 0);
	m_levelScale = Math::Matrix::CreateScale(m_levelSize.x, m_levelSize.y, 0);
	m_levelMat = m_levelScale * m_levelTrans;
}

void C_Level::Level2Init()
{
	m_levelPos = { 400,-60 };
	m_levelSize = { 1.0f,1.0f };
	m_alpha2 = 0.0f;
	m_levelTex.Load("Texture/Level/Level2.png");
	m_level2Flg = false;
    m_alpha2Speed = 0.01f;
}

// ================================================================
// Level 3 処理
// ================================================================

void C_Level::Level3Init()
{
    // 座標とサイズの設定
    m_level3Pos = { 400, -60 };
    m_level3Size = { 1.0f, 1.0f };
    m_alpha3 = 0.0f;
    m_alpha3Speed = 0.01f;

    // テクスチャの読み込み
    m_level3Tex.Load("Texture/Level/Level3.png");

    // 初期状態は非表示
    m_level3Flg = false;
}

void C_Level::Level3Update()
{
    // 自分が有効ならフェードイン
    if (m_level3Flg)
    {
        m_alpha3 += m_fadeSpeed;
        if (m_alpha3 >= 1.0f) { m_alpha3 = 1.0f; }
    }

    

    // 行列計算（Zスケールは必ず 1.0f）
    m_level3Scale = Math::Matrix::CreateScale(m_level3Size.x, m_level3Size.y, 1.0f);
    m_level3Trans = Math::Matrix::CreateTranslation(m_level3Pos.x, m_level3Pos.y, 0.0f);
    m_level3Mat = m_level3Scale * m_level3Trans;
}

void C_Level::Level3Draw()
{
    // 透明度が 0 より大きい間は描画を続ける
    if (m_alpha3 > 0.0f)
    {
        SHADER.m_spriteShader.SetMatrix(m_level3Mat);
        // Rectangle の範囲は画像のサイズに合わせて調整してください
        SHADER.m_spriteShader.DrawTex(&m_level3Tex, Math::Rectangle(0, 0, 140, 50), m_alpha3);
    }
}

// ================================================================
// Level Max 処理
// ================================================================

void C_Level::LevelMaxInit()
{
    m_levelMaxPos = { 440,-60 };
    m_levelMaxSize = { 1.0f, 1.0f };
    m_alphaMax = 0.0f;

    m_levelMaxTex.Load("Texture/Level/LevelMax.png");

    m_levelMaxFlg = false;
}

void C_Level::LevelMaxUpdate()
{

    if(m_levelMaxFlg)
    {
        m_alpha3 -= m_alpha3Speed;

        if (m_alpha3 <= 0.0f)
        {
            m_alpha3 = 0.0f;
            m_level3Flg = false;
        }

    }

    // 自分が有効ならフェードイン
    if (m_levelMaxFlg)
    {
        m_alphaMax += m_fadeSpeed;
        if (m_alphaMax >= 1.0f) { m_alphaMax = 1.0f; }
    }

    // 行列計算
    m_levelMaxScale = Math::Matrix::CreateScale(m_levelMaxSize.x, m_levelMaxSize.y, 1.0f);
    m_levelMaxTrans = Math::Matrix::CreateTranslation(m_levelMaxPos.x, m_levelMaxPos.y, 0.0f);
    m_levelMaxMat = m_levelMaxScale * m_levelMaxTrans;
}

void C_Level::LevelMaxDraw()
{
    // 透明度が 0 より大きい間は描画を続ける
    if (m_alphaMax > 0.0f)
    {
        SHADER.m_spriteShader.SetMatrix(m_levelMaxMat);
        SHADER.m_spriteShader.DrawTex(&m_levelMaxTex, Math::Rectangle(0, 0, 244, 41), m_alphaMax);
    }
}

