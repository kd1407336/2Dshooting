#include "Score.h"

void C_Score::Draw()
{
    std::string score = std::to_string(m_score);

    float x = m_pos.x;
    float y = m_pos.y;

    int digitWidth = 16;   // ”š1Œ…‚Ì•
    int digitHeight = 32;  // ”š‚Ì‚‚³
    int spacing = 3;       // © ‚±‚±‚ğ•Ï‚¦‚é‚ÆŠÔŠu‚ª•Ï‚í‚é

    if(m_scoreFlg)
    {
        for (int i = 0; i < score.size(); i++)
        {
            int num = score[i] - '0'; // •¶š ¨ ”š

            // ”š1‚Â•ª‚ÌØ‚èæ‚è”ÍˆÍ
            Math::Rectangle rect = { num * digitWidth, 0, digitWidth, digitHeight };

            // š Œ…‚ÌŠÔŠu‚ğ’Ç‰Á
            Math::Matrix trans = Math::Matrix::CreateTranslation(x + i * (digitWidth + spacing), y, 0);

            SHADER.m_spriteShader.SetMatrix(trans);

            // •`‰æ
            SHADER.m_spriteShader.DrawTex(&m_tex, rect, 1.0f);
        }
    }

}

void C_Score::Update()
{
    if (m_scoreFlg)
    {
        m_scoreTimer--;

        if (m_scoreTimer <= m_timerLimit)
        {
            m_scoreFlg = false;
            m_scoreTimer = m_timerReset;
        }
    }

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
    m_scoreTimer = 180;
    m_timerLimit = 0;
    m_timerReset = 180;
    m_scoreFlg = false;
}
