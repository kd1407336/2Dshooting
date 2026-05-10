#include "TitleScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Fade/FadeIn.h"
#include "Application/GameScene/GameScene.h"
#include "Application/MouseManager/MouseManager.h"

extern MouseManager g_mouse;


void C_TitleScene::Draw()
{
	ScreenDraw();

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
	ScreenUpdate();

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
	ScreenInit();
	
	m_fadeOut = new C_FadeOut();
	if (m_fadeOut) { m_fadeOut->Init(); }

	m_fadeIn = new C_FadeIn();
	if (m_fadeIn) { m_fadeIn->Init(); }

	m_fadeInFlg = false;

}

void C_TitleScene::StartDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_startMat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, Math::Rectangle(0, 0, 69, 50), m_alpha);
}

void C_TitleScene::StartUpdate()
{

	m_alpha += m_delet;

	if (m_alpha >= m_alphaMax)
	{
		m_alpha = m_alphaMax;
		m_alpha -= m_delet;
	}

	if (m_alpha <= m_alphaMin)
	{
		m_alpha = m_alphaMin;
		m_alpha = m_delet;
	}


	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_fadeOut->SetFlg(true);
	}

	/*float dx = m_startPos.x - g_mouse.GetPos().x;
	float dy = m_startPos.y - g_mouse.GetPos().y;
	float c = sqrt(dx * dx + dy * dy);


	if (c < 40)
	{
		m_startSize = { 2.5f,2.5f };

	

	}
	else
	{
		m_startSize = { 1.7f,1.7f };
	}*/

	m_startTrans = Math::Matrix::CreateTranslation(m_startPos.x, m_startPos.y, 0);
	m_startScale = Math::Matrix::CreateScale(m_startSize.x, m_startSize.y, 0);
	m_startMat = m_startScale * m_startTrans;	
}

void C_TitleScene::StartInit()
{
	m_startPos = { 0,0 };
	m_startSize = { 1.7f,1.7f };
	m_alpha = 1.0f;
	m_alphaMax = 1.0f;
	m_alphaMin = 0.2f;
	m_delet = 0.05f;
	m_startTex.Load("Texture/Title/Start.png");
}

void C_TitleScene::ScreenDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_screenMat);
	SHADER.m_spriteShader.DrawTex(&m_screenTex, Math::Rectangle(0, 0, 320, 320), 1.0f);
}

void C_TitleScene::ScreenUpdate()
{
	m_screenTrans = Math::Matrix::CreateTranslation(m_screenPos.x, m_screenPos.y, 0);
	m_screenScale = Math::Matrix::CreateScale(m_screenSize.x, m_screenSize.y, 0);
	m_screenMat = m_screenScale * m_screenTrans;
}

void C_TitleScene::ScreenInit()
{
	m_screenPos = { 0,0 };
	m_screenSize = { 4.0f,4.0f };
	m_screenTex.Load("Texture/Title/Screen.png");
}

void C_TitleScene::Release()
{
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
}
