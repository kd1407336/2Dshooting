#include "TitleScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Fade/FadeIn.h"
#include "Application/GameScene/GameScene.h"

C_TitleScene::C_TitleScene()
{
	
}

C_TitleScene::~C_TitleScene()
{
	if (m_fadeIn) { delete m_fadeIn; }
	if (m_fadeOut) { delete m_fadeOut; }
}

void C_TitleScene::Draw()
{
	if (m_fadeOut ) { m_fadeOut->Draw(); }
	if(m_fadeIn && m_fadeInFlg){m_fadeIn->Draw();}
	
}

void C_TitleScene::Update()
{
	if (m_fadeOut) { m_fadeOut->Update(); }

	if (m_fadeInFlg)
	{
		if (m_fadeIn)
		{
			m_fadeIn->Update();
		}
	}

	

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
	m_fadeOut = new C_FadeOut();
	if (m_fadeOut) { m_fadeOut->Init(); }

	m_fadeIn = new C_FadeIn();
	if (m_fadeIn) { m_fadeIn->Init(); }
	
	if (SCENEMANAGER.GetRequestFadeIn())
	{
		m_fadeInFlg = true;        // ★ このシーンのフェードイン開始
		m_fadeIn->SetFlg(true);
		SCENEMANAGER.SetRequestFadeIn(false);
	}

	m_fadeInFlg = false;

}
