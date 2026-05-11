#pragma once
#include "Application/State/State.h"


class C_FadeOut;
class C_FadeIn;

class C_TitleScene : public C_State
{
public:

	C_TitleScene() {}
	~C_TitleScene()override { Release(); }

	void Draw()override;
	void Update()override;
	void Init()override;

	void StartDraw();
	void StartUpdate();
	void StartInit();

	void ScreenDraw();
	void ScreenUpdate();
	void ScreenInit();

	void PlayDraw();
	void PlayUpdate();
	void PlayInit();

	void SpaceDraw();
	void SpaceUpdate();
	void SpaceInit();

	void SetFadeInFlg(bool fadeinflg) { m_fadeInFlg = fadeinflg; }
	bool GetFadeInFlg() { return m_fadeInFlg; }

private:

	C_FadeOut* m_fadeOut = nullptr;
	C_FadeIn* m_fadeIn = nullptr;

	bool m_fadeInFlg;

	Math::Vector2 m_startPos;
	Math::Vector2 m_startSize;
	Math::Matrix m_startMat;
	Math::Matrix m_startScale;
	Math::Matrix m_startTrans;
	KdTexture m_startTex;

	Math::Vector2 m_screenPos;
	Math::Vector2 m_screenSize;
	Math::Matrix m_screenMat;
	Math::Matrix m_screenTrans;
	Math::Matrix m_screenScale;
	KdTexture    m_screenTex;

	Math::Matrix m_screen1Pos;
	Math::Matrix m_screen1Size;
	Math::Matrix m_screen1Mat;
	Math::Matrix m_screen1Scale;
	Math::Matrix m_screen1Trans;

	Math::Vector2 m_playPos;
	Math::Vector2 m_playSize;
	Math::Matrix m_playMat;
	Math::Matrix m_playScale;
	Math::Matrix m_playTrans;
	KdTexture    m_playTex;

	Math::Vector2 m_spacePos;
	Math::Vector2 m_spaceSize;
	Math::Matrix m_spaceMat;
	Math::Matrix m_spaceScale;
	Math::Matrix m_spaceTrans;
	KdTexture    m_spaceTex;

	float m_alpha;
	float m_alphaSpeed;
	float m_alphaMax;
	float m_alphaMin;
	float m_delet;
	float m_alphaReset;

	void Release();

};