#pragma once
#include "Application/State/State.h"
#include "Application/Player/Player.h"
#include "Application/Fade/FadeIn.h"
#include "Application/Enemy/EnemyBase.h"
#include "Application/Score/Score.h"

class C_Enemy;
class C_FadeOut;
class C_TitleScene;
class C_Timer;

class C_GameScene : public C_State
{
public:
	C_GameScene();
	~C_GameScene()override;

	void Draw() override;
	void Update() override;
	void Init() override;

	

	bool GetFadeInFlg() { return m_fadeInFlg; }

	void Action()override;
	void TimerUpdate()override;
	void ScoreUpdate()override;

private:

	C_Player* m_player = nullptr;
	C_FadeIn* m_fadeIn = nullptr;
	C_FadeOut* m_fadeOut = nullptr;
	C_Timer* m_timer = nullptr;

	static const int m_scoreMax = 11;
	C_Score m_score[m_scoreMax];

	std::vector<std::unique_ptr<C_Enemy>> m_enemies;

	bool m_fadeInFlg;
	bool m_resultFadeFlg;
	bool m_titleFadeFlg;

	int m_radius;
	int m_bulletRadius;
	int m_enemyRadius;

	int m_maxEnemies;

	int m_killPoint;
	int m_totalScore;
	int m_displayScore;

};