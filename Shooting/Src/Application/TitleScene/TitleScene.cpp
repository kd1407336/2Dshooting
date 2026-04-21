#include "TitleScene.h"
#include "Application/SceneManager/SceneManager.h"

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
		SCENEMANAGER.ChangeState(new C_GameScene());
	}

}

void C_TitleScene::Init()
{
	m_fadeOut->Init();
	
}
