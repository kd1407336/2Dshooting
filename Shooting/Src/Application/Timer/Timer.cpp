#include "Timer.h"

void C_Timer::Draw()
{
	std::string score = std::to_string(m_timerCnt);

	float x = m_pos.x;
	float y = m_pos.y;

	int digitWidth = 16;   // ”š1Œ…‚Ì•
	int digitHeight = 32;  // ”š‚Ì‚‚³
	int spacing = 5;       // © ‚±‚±‚ğ•Ï‚¦‚é‚ÆŠÔŠu‚ª•Ï‚í‚é


	for (int i = 0; i < score.size(); i++)
	{
		int num = score[i] - '0'; // •¶š ¨ ”š

		// ”š1‚Â•ª‚ÌØ‚èæ‚è”ÍˆÍ
		Math::Rectangle rect = { num * digitWidth, 0, digitWidth, digitHeight };
		Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

		// š Œ…‚ÌŠÔŠu‚ğ’Ç‰Á
		Math::Matrix trans = Math::Matrix::CreateTranslation(x + i * (digitWidth + spacing), y, 0);

		SHADER.m_spriteShader.SetMatrix(trans);

		// •`‰æ
		SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rect, &color);
	}

}

void C_Timer::Update()
{
	if (m_timerFlg)
	{
		m_timer++; 
		m_totalFrame++;
	}
	
	if (m_timer >= m_timerLimit)
	{
		m_timerCnt += 1;
		m_timer = m_timerReset;
	}


	m_trans = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y,0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;

}

void C_Timer::Init()
{
	m_pos = { 0,320 };
	m_size = { 1.0f,1.0f };
	m_timer = 0;
	m_timerCnt = 0;
	m_timerLimit = 60;
	m_timerReset = 0;
	m_timerFlg = false;
	m_tex.Load("Texture/Timer/Suuji.png");
}
