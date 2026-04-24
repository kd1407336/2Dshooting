#include "GameScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Enemy/Enemy.h"

C_GameScene::C_GameScene()
{
	m_player = new C_Player();
	m_fadeIn = new C_FadeIn();
	m_fadeOut = new C_FadeOut();
	m_enemy = new C_Enemy();
}

C_GameScene::~C_GameScene()
{
	if (m_player) { delete m_player; m_player = nullptr; }
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
	if (m_enemy) { delete m_enemy;m_enemy = nullptr; }
}

void C_GameScene::Draw()
{
	//プレイヤー
	if (m_player) { m_player->Draw(); }
	if (m_enemy) { m_enemy->Draw(); }

	if (m_fadeIn) { m_fadeIn->Draw(); }
	if (m_fadeOut) { m_fadeOut->Draw(); }
}

void C_GameScene::Update()
{
	m_fadeIn->SetFlg(true);

	//プレイヤー更新
	if (m_player) { m_player->Update(); }
	if (m_enemy) { m_enemy->Update(); }
	
	//フェードイン更新
	if(m_fadeIn->GetFlg()){m_fadeIn->Update();}

	//フェードアウト更新
	if (m_fadeOut->GetFlg()) { m_fadeOut->Update(); }

	//タイトルに戻る時にフェード処理を実行する
	if (GetAsyncKeyState('T') & 0x8000)
	{
		//タイトルに戻るときはこのフラグをtrueにする
		m_titleFadeFlg = true;

		//フェードアウト処理が始まるようにする
		m_fadeOut->SetFlg(true);
	}

	if (!m_player->GetAliveFlg())
	{
		//リザルトに戻るときはこのフラグをtrueにする
		m_resultFadeFlg = true;

		//フェードアウト処理を実行する
		m_fadeOut->SetFlg(true);

	}

	float dx = m_player->GetPos().x - m_enemy->GetPos().x;
	float dy = m_player->GetPos().y - m_enemy->GetPos().y;
	float c = sqrt(dx * dx + dy * dy);

	if (c < 50)
	{
		m_player->SetHitFlg(true);
	}
	else
	{
		m_player->SetHitFlg(false);
	}

	
	//フェードアウト処理が終わっていたら
	//シーンを切り替える
	if (m_fadeOut->GetFadeFinish()&& m_titleFadeFlg)		
	{
		//タイトルシーンでフェードイン処理が始まるようにする
		SCENEMANAGER.SetRequestFadeIn(true);
		//タイトルシーンに戻る
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
	else if (m_fadeOut->GetFadeFinish() && m_resultFadeFlg)	
	{
		//リザルトシーンでフェードイン処理が始まるようにする
		SCENEMANAGER.SetRequestFadeIn(true);
		
		//シーンをリザルトに切り替える
		SCENEMANAGER.ChangeState(new C_ResultScene());
	}

}

void C_GameScene::Init()
{
	if (m_player) { m_player->Init(); }
	if (m_enemy) { m_enemy->Init(); }
	if (m_fadeIn) { m_fadeIn->Init(); }
	if (m_fadeOut) { m_fadeOut->Init(); }
	m_fadeInFlg = false;
	m_titleFadeFlg = false;
	m_resultFadeFlg = false;

}
