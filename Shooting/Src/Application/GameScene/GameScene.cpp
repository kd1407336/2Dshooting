#include "GameScene.h"

C_GameScene::C_GameScene()
{
	m_player = new C_Player();
	m_fadeIn = new C_FadeIn();
}

C_GameScene::~C_GameScene()
{
	if (m_player) { delete m_player; m_player = nullptr; }
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
}

void C_GameScene::Draw()
{
	if (m_player)m_player->Draw();
	if (m_fadeIn)m_fadeIn->Draw();
}

void C_GameScene::Update()
{
	if (m_player)m_player->Update();
	if (m_fadeIn)m_fadeIn->Update();

	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_player->SetFlg(false);
	}

}

void C_GameScene::Init()
{
	if (m_player)m_player->Init();
	if (m_fadeIn)m_fadeIn->Init();
}
