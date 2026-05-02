#include "Fade.h"

void C_Fade::Drwa()
{
	if (!m_flg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
}

void C_Fade::Update()
{

}

void C_Fade::Init()
{
	m_tex.Load("Texture/Fade/FadeOut.png");
}
