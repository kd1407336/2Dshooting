#pragma once
#include "Application/State/State.h"

class C_FadeIn;
class C_FadeOut;

class C_ResultScene : public C_State
{
public:

	C_ResultScene(){}
	~C_ResultScene() { Release(); }
	
	void Draw();
	void Update();
	void Init();

private:

	C_FadeIn* m_fadeIn = nullptr;
	C_FadeOut* m_fadeOut = nullptr;

	void Release();

};