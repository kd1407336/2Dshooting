#pragma once
#include "Application/State/State.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Fade/FadeIn.h"



class C_TitleScene : public C_State
{
public:

	C_TitleScene();
	~C_TitleScene();

	void Draw()override;
	void Update()override;
	void Init()override;

private:

	C_FadeOut* m_fadeOut = nullptr;
	

};