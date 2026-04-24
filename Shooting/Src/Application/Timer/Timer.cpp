#include "Timer.h"

void C_Timer::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_Timer::Update()
{
	
}

void C_Timer::Init()
{

}
