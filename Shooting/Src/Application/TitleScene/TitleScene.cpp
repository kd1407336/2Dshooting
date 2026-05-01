#include "TitleScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Fade/FadeIn.h"
#include "Application/GameScene/GameScene.h"
#include "Application/MouseManager/MouseManager.h"

extern MouseManager g_mouse;

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
	StartDraw();

	if (m_fadeOut ) { m_fadeOut->Draw(); }
	if(m_fadeIn && SCENEMANAGER.GetRequestFadeIn()){m_fadeIn->Draw();}
}

void C_TitleScene::Update()
{
	if (m_fadeOut) { m_fadeOut->Update(); }
	if (m_fadeIn){m_fadeIn->Update();}

	g_mouse.Update();
	StartUpdate();
	

	if (SCENEMANAGER.GetRequestFadeIn())
	{
		m_fadeIn->SetFlg(true);
	}

	if (GetAsyncKeyState('G') & 0x8000)
	{
		
	}

	if (m_fadeOut->GetFadeFinish())
	{
		SCENEMANAGER.ChangeState(new C_GameScene());
	}

}

void C_TitleScene::Init()
{
	StartInit();
	
	m_fadeOut = new C_FadeOut();
	if (m_fadeOut) { m_fadeOut->Init(); }

	m_fadeIn = new C_FadeIn();
	if (m_fadeIn) { m_fadeIn->Init(); }

	m_fadeInFlg = false;

}

void C_TitleScene::StartDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_startMat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, Math::Rectangle(0, 0, 69, 50), 1.0f);
}

void C_TitleScene::StartUpdate()
{
	float dx = m_startPos.x - g_mouse.GetPos().x;
	float dy = m_startPos.y - g_mouse.GetPos().y;
	float c = sqrt(dx * dx + dy * dy);

	if (c < 40)
	{
		m_startSize = { 2.5f,2.5f };

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_fadeOut->SetFlg(true);
		}

	}
	else
	{
		m_startSize = { 1.7f,1.7f };
	}

	m_startTrans = Math::Matrix::CreateTranslation(m_startPos.x, m_startPos.y, 0);
	m_startScale = Math::Matrix::CreateScale(m_startSize.x, m_startSize.y, 0);
	m_startMat = m_startScale * m_startTrans;	
}

void C_TitleScene::StartInit()
{
	m_startPos = { 0,0 };
	m_startSize = { 1.7f,1.7f };
	m_startTex.Load("Texture/Title/Start.png");
}
