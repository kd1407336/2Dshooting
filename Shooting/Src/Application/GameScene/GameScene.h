#pragma once
#include "Application/State/State.h"
#include "Application/Player/Player.h"
#include "Application/Fade/FadeIn.h"
#include "Application/Enemy/EnemyBase.h"

class C_FadeOut;
class C_TitleScene;
class C_Enemy;

class C_GameScene : public C_State
{
public:
	C_GameScene();
	~C_GameScene();

	void Draw() override;
	void Update() override;
	void Init() override;

	bool GetFadeInFlg() { return m_fadeInFlg; }

	void Action();
	

private:

	C_Player* m_player = nullptr;
	C_FadeIn* m_fadeIn = nullptr;
	C_FadeOut* m_fadeOut = nullptr;
	C_Enemy* m_enemy = nullptr;

	bool m_fadeInFlg;
	bool m_resultFadeFlg;
	bool m_titleFadeFlg;

	int m_radius;
	int m_bulletRadius;


};