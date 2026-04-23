#include "Result.h"
#include "../Fade/FadeIn.h"
#include "../Fade/FadeOut.h"
#include "Application/SceneManager/SceneManager.h"

void C_ResultScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);

	if(m_fadeIn){m_fadeIn->Draw();}
	if(m_fadeOut){m_fadeOut->Draw();}

}

void C_ResultScene::Update()
{
	if (m_fadeIn) { m_fadeIn->Update(); }
	if (m_fadeOut) { m_fadeOut->Update(); }

	if (SCENEMANAGER.GetRequestFadeIn())
	{
		m_fadeIn->SetFlg(true);
	}

	//タイトルシーンに戻る
	if (GetAsyncKeyState('T') & 0x8000)
	{
		m_fadeOut->SetFlg(true);
	}

	if (m_fadeOut->GetFadeFinish())
	{
		//タイトルシーンでフェードイン処理が始まるようにする
		SCENEMANAGER.SetRequestFadeIn(true);

		SCENEMANAGER.ChangeState(new C_TitleScene());
	}

	

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_ResultScene::Init()
{
	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };

	//フェードイン
	m_fadeIn = new C_FadeIn();
	if (m_fadeIn) { m_fadeIn->Init(); }

	//フェードアウト
	m_fadeOut = new C_FadeOut();
	if (m_fadeOut) { m_fadeOut->Init(); }
	

}

void C_ResultScene::Release()
{
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
}
