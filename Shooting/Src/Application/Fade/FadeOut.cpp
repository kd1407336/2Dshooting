#include "FadeOut.h"

C_FadeOut::C_FadeOut()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f};
	m_alpha = 0.0f;
	m_fadeSpeed = 0.03f;
	m_alphaMax = 1.0f;
	m_alphaReset = 0.0f;
	m_flg = false;
	m_fadeFinish = false;
}

C_FadeOut::~C_FadeOut()
{
	m_tex.Release();
}

void C_FadeOut::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), m_alpha);
}

void C_FadeOut::Update()
{
	if (m_flg)
	{
		m_alpha += m_fadeSpeed;
	}

	if (m_alpha >= m_alphaMax)
	{
		m_fadeFinish = true;
	}


}

void C_FadeOut::Init()
{
	m_tex.Load("Texture/Fade/FadeOut.png");
}
