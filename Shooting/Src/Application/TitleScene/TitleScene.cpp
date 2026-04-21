#include "TitleScene.h"

C_TitleScene::C_TitleScene()
{
	m_fadeOut = new C_FadeOut();
	m_fadeIn = new C_FadeIn();
}

C_TitleScene::~C_TitleScene()
{

}

void C_TitleScene::Draw()
{
	m_fadeOut->Draw();
	m_fadeIn->Draw();
}

void C_TitleScene::Update()
{
	m_fadeOut->Update();
	m_fadeIn->Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_fadeOut->SetFlg(true);
	}

}

void C_TitleScene::Init()
{
	m_fadeOut->Init();
	m_fadeIn->Init();
}
