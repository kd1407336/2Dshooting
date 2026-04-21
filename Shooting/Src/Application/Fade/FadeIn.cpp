#include "FadeIn.h"

C_FadeIn::C_FadeIn()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	m_alpha = 1.0f;
	m_fadeSpeed = 0.02f;
	m_alphaMin = 0.0f;
	m_alphaReset = 1.0f;
	m_flg = false;
	m_fadeFinish = false;
}

C_FadeIn::~C_FadeIn()
{
	m_tex.Release();
}

void C_FadeIn::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), m_alpha);
}

void C_FadeIn::Update()
{

	if(m_flg)
	{
		m_alpha -= m_fadeSpeed;
	}
	
	if (m_alphaMin < m_alpha)
	{
		m_fadeFinish = true;
	}


}

void C_FadeIn::Init()
{
	m_tex.Load("Texture/Fade/FadeOut.png");
}
