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

	PlayDraw();

	SpaceDraw();

	StartDraw();

	if (m_fadeOut ) { m_fadeOut->Draw(); }
	if(m_fadeIn && SCENEMANAGER.GetRequestFadeIn()){m_fadeIn->Draw();}
}

void C_TitleScene::Update()
{
	if (m_fadeOut) { m_fadeOut->Update(); }
	if (m_fadeIn){m_fadeIn->Update();}

	PlayUpdate();
	g_mouse.Update();
	StartUpdate();
	ScreenUpdate();
	SpaceUpdate();
	

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
	
	ScreenInit();
	PlayInit();
	SpaceInit();
	
	m_fadeOut = new C_FadeOut();
	if (m_fadeOut) { m_fadeOut->Init(); }

	m_fadeIn = new C_FadeIn();
	if (m_fadeIn) { m_fadeIn->Init(); }

	m_fadeInFlg = false;

}

void C_TitleScene::StartDraw()
{
	
}

void C_TitleScene::StartUpdate()
{


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

	SHADER.m_spriteShader.SetMatrix(m_screen1Mat);
	SHADER.m_spriteShader.DrawTex(&m_screenTex, Math::Rectangle(0, 0, 320, 320), 1.0f);
}

void C_TitleScene::ScreenUpdate()
{
	m_screenPos.y -= 3;

	if (m_screenPos.y <= -720)
	{
		m_screenPos.y = 0;
	}

	m_screenTrans = Math::Matrix::CreateTranslation(m_screenPos.x, m_screenPos.y, 0);
	m_screenScale = Math::Matrix::CreateScale(m_screenSize.x, m_screenSize.y, 0);
	m_screenMat = m_screenScale * m_screenTrans;

	m_screen1Trans = Math::Matrix::CreateTranslation(m_screenPos.x, m_screenPos.y + 720, 0);
	m_screen1Scale = Math::Matrix::CreateScale(m_screenSize.x, m_screenSize.y, 0);
	m_screen1Mat = m_screen1Scale * m_screen1Trans;
}

void C_TitleScene::ScreenInit()
{
	m_screenPos = { 0,0 };
	m_screenSize = { 4.0f,2.5f };
	m_screenTex.Load("Texture/Title/Screen.png");
}

void C_TitleScene::PlayDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_playMat);
	SHADER.m_spriteShader.DrawTex(&m_playTex, Math::Rectangle(0, 0, 261, 60), m_alpha);
}

void C_TitleScene::PlayUpdate()
{

	// アルファ値を更新
	m_alpha += m_alphaSpeed;

	// 最小値（0.0fなど）以下になったら、増やす方向に反転
	if (m_alpha <= m_alphaMin)
	{
		m_alpha = m_alphaMin;
		m_alphaSpeed *= -1.0f; // ★ -1.0f で向きだけ変える
	}
	// 最大値（1.0fなど）以上になったら、減らす方向に反転
	else if (m_alpha >= m_alphaMax)
	{
		m_alpha = m_alphaMax;
		m_alphaSpeed *= -1.0f; // ★ -1.0f で向きだけ変える
	}


	m_playTrans = Math::Matrix::CreateTranslation(m_playPos.x, m_playPos.y, 0);
	m_playScale = Math::Matrix::CreateScale(m_playSize.x, m_playSize.y, 0);
	m_playMat = m_playScale * m_playTrans;
}

void C_TitleScene::PlayInit()
{
	m_playPos = { 0,-100 };
	m_playSize = { 1.5f,1.5f };
	
	m_alpha = 1.0f;
	m_alphaSpeed = 0.02f;
	m_alphaMin = 0.3f;
	m_alphaMax = 1.0f;
	m_alphaReset = 1.0f;

	m_playTex.Load("Texture/Title/Play.png");
}

void C_TitleScene::SpaceDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_spaceMat);
	SHADER.m_spriteShader.DrawTex(&m_spaceTex, Math::Rectangle(0, 0, 430, 70), 1.0f);
}

void C_TitleScene::SpaceUpdate()
{
	m_spaceTrans = Math::Matrix::CreateTranslation(m_spacePos.x, m_spacePos.y, 0);
	m_spaceScale = Math::Matrix::CreateScale(m_spaceSize.x, m_spaceSize.y, 0);
	m_spaceMat = m_spaceScale * m_spaceTrans;
}

void C_TitleScene::SpaceInit()
{
	m_spacePos = { 15,150 };
	m_spaceSize = { 1.5f,2.0f };
	m_spaceTex.Load("Texture/Title/SpaceShooter.png");
}

void C_TitleScene::Release()
{
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
}
