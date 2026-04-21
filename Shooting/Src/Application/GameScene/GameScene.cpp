#include "GameScene.h"

C_GameScene::C_GameScene()
{
	m_player = new C_Player();
}

C_GameScene::~C_GameScene()
{
	if (m_player) { delete m_player; m_player = nullptr; }
}

void C_GameScene::Draw()
{
	if (m_player)m_player->Draw();
}

void C_GameScene::Update()
{
	if (m_player)m_player->Update();

	if (GetAsyncKeyState('K') & 0x8000)
	{
		m_player->SetFlg(false);
	}

}

void C_GameScene::Init()
{
	if (m_player)m_player->Init();
}
