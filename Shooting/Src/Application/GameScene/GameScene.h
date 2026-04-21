#pragma once
#include "Application/State/State.h"
#include "Application/Player/Player.h"
#include "Application/Fade/FadeIn.h"

class C_GameScene : public C_State
{
public:
	C_GameScene();
	~C_GameScene();

	void Draw() override;
	void Update() override;
	void Init() override;

private:

	C_Player* m_player = nullptr;
	C_FadeIn* m_fadeIn = nullptr;

};