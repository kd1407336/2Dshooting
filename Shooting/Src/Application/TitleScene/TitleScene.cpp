#include "TitleScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"

C_TitleScene::C_TitleScene()
{
	m_fadeOut = new C_FadeOut();
}

C_TitleScene::~C_TitleScene()
{

}

void C_TitleScene::Draw()
{
	m_fadeOut->Draw();
	
}

void C_TitleScene::Update()
{
	m_fadeOut->Update();
	
	if (GetAsyncKeyState('G') & 0x8000)
	{
		m_fadeOut->SetFlg(true);
	}

	if (m_fadeOut->GetFadeFinish())
	{
		SCENEMANAGER.ChangeState(new C_GameScene());
	}

}

void C_TitleScene::Init()
{
	m_fadeOut->Init();
	
}
