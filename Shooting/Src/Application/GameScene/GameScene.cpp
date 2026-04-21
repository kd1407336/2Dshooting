#include "GameScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"


C_GameScene::C_GameScene()
{
	m_player = new C_Player();
	m_fadeIn = new C_FadeIn();
	m_fadeOut = new C_FadeOut();
}

C_GameScene::~C_GameScene()
{
	if (m_player) { delete m_player; m_player = nullptr; }
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
}

void C_GameScene::Draw()
{
	if(m_fadeIn->GetFadeFinish()){m_player->Draw();}
	if (m_fadeIn) { m_fadeIn->Draw(); }
	if (m_fadeOut) { m_fadeOut->Draw(); }
}

void C_GameScene::Update()
{
	m_fadeIn->SetFlg(true);

	if (m_fadeIn->GetFadeFinish()) { m_player->Update(); }
	
	//フェードイン更新
	if(m_fadeIn->GetFlg()){m_fadeIn->Update();}

	//フェードアウト更新
	if (m_fadeOut->GetFlg()) { m_fadeOut->Update(); }

	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_player->SetFlg(false);
	}

	if (GetAsyncKeyState('T') & 0x8000)
	{
		//フェードアウト処理が始まるようにする
		m_fadeOut->SetFlg(true);
	}

	if (m_fadeOut->GetFadeFinish())
	{
		//タイトルシーンに戻る
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}

}

void C_GameScene::Init()
{
	if (m_player)m_player->Init();
	if (m_fadeIn)m_fadeIn->Init();
	if (m_fadeOut) { m_fadeOut->Init(); }
}
