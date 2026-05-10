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

	float m_alpha;;
	float m_alphaMax;
	float m_alphaMin;
	float m_delet;

	void Release();

};