#include "Key.h"

void C_Key::Draw()
{
	if (!m_aliveFlg)return;
    Math::Rectangle rect = { 0,0,90,90 };
    Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);
}

void C_Key::Update()
{
	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_Key::Init(KeyType type)
{
    m_type = type;
    m_size = { 0.4f, 0.4f };

    m_alpha = 1.0f;
    m_aliveFlg = true;

    // 種類に応じて画像を読み込み、位置を決める
    switch (m_type) 
    {
    case KeyType::Up:
        m_tex.Load("Texture/Key/Up.png");
        m_pos = { 400, -180 }; // 上の位置
        break;
    case KeyType::Down:
        m_tex.Load("Texture/Key/Down.png");
        m_pos = { 387, -220 }; // 下の位置
        break;
    case KeyType::Left:
        m_tex.Load("Texture/Key/Left.png");
        m_pos = { 350, -220 }; // 左の位置
        break;
    case KeyType::Right:
        m_tex.Load("Texture/Key/Right.png");
        m_pos = { 430, -220 }; // 右の位置
        break;
    }

}

