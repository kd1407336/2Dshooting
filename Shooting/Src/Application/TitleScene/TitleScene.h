#pragma once
#include "Application/State/State.h"

class C_FadeOut;
class C_FadeIn;

class C_TitleScene : public C_State
{
public:

	C_TitleScene();
	~C_TitleScene();

	void Draw()override;
	void Update()override;
	void Init()override;

	void SetFadeInFlg(bool fadeinflg) { m_fadeInFlg = fadeinflg; }
	bool GetFadeInFlg() { return m_fadeInFlg; }

private:

	C_FadeOut* m_fadeOut = nullptr;
	C_FadeIn* m_fadeIn = nullptr;

	bool m_fadeInFlg;

};