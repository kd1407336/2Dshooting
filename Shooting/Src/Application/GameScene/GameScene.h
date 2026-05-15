#pragma once
#include "Application/State/State.h"
#include "Application/Fade/FadeIn.h"
#include "Application/Enemy/EnemyBase.h"
#include "Application/Result/Result.h"
#include "Application/Score/Score.h"
#include "Application/Explosion/Explosion.h"
#include "Application/Enemy/Enemy.h"
#include "Application/EnemyBullet/EnemyBullet.h"
#include "Application/EnemyBullet/BossBullet.h"
#include "Application/Key/Key.h"
#include <memory>

class C_Enemy;
class C_BossEnemy;
class C_BossBullet;
class C_EnemyBullet;
class C_EnemyBullet;
class C_Explosion;
class C_FadeOut;
class C_GameClear;
class C_GameOver;
class C_GameScreen;
class C_HomeIcon;
class C_Image;
class C_Key;
class C_Level;
class C_Player;
class C_TitleScene;
class C_Timer;
class C_Window;

class C_GameScene : public C_State
{
public:
	C_GameScene() {}
	~C_GameScene()override { Release(); }

	void Draw() override;
 
	void Update() override;
	void Init() override;


	bool GetFadeInFlg() { return m_fadeInFlg; }

	void Action()override;
	void TimerUpdate()override;
	void ScoreUpdate()override;
	void HomeIconUpdate()override;
	float GetSafeRandomX();


	void CountDownDraw();
	void CountDownUpdate();
	void CountDownInit();

	void StartLogoDraw();
	void StartLogoUpdate();


private:

	C_Player*		m_player = nullptr;
	C_FadeIn*		m_fadeIn = nullptr;
	C_FadeOut*		m_fadeOut = nullptr;
	C_GameScreen*	m_gameScreen = nullptr;
	C_GameClear*	m_gameClear = nullptr;
	C_GameOver*		m_gameOver = nullptr;
	C_Timer*		m_timer = nullptr;
	C_HomeIcon*		m_homeIcon= nullptr;
	C_Level*		m_level = nullptr;
	C_BossEnemy*	m_bEnemy = nullptr;
	C_Window*		m_window = nullptr;
	C_Image*		m_image = nullptr;
	C_Key*			m_key = nullptr;

	// 爆発の最大数（画面内に同時に出せる数）
	static const int m_explosionMax = 10;

	std::vector<std::unique_ptr<C_Explosion>> m_explosions;
	std::vector<std::unique_ptr<C_EnemyBullet>> m_enemyBullets;
	std::vector<std::unique_ptr<C_BossBullet>> m_bossBullets;
	static const int m_scoreMax = 15;
	C_Score m_score[m_scoreMax];

	const int m_bulletMax = 30;

	std::vector<std::unique_ptr<C_Enemy>> m_enemies;


	Math::Vector2 m_startPos;
	Math::Vector2 m_startSize;
	Math::Matrix  m_startMat;
	Math::Matrix  m_startScale;
	Math::Matrix  m_startTrans;
	KdTexture     m_startTex;   // 画像データ

	Math::Vector2 m_countPos;
	Math::Vector2 m_countSize;
	Math::Matrix  m_countMat;
	Math::Matrix  m_countScale;
	Math::Matrix  m_countTrans;
	KdTexture     m_countTex;


	float m_startAlpha = 1.0f;     // STARTロゴの透明度 
	float m_startAlphaMin = 0.0f;
	KdTexture m_startLogoTex;      
	float m_countDownScale = 1.0f; 


	bool m_fadeInFlg;
	bool m_resultFadeFlg;
	bool m_titleFadeFlg;

	bool m_isGameOver;
	bool m_isGameClear;
	int m_gameOverTimer;
	int m_gameClearTimer;

	int m_radius;
	int m_charaRadius; 
	int m_bulletRadius;
	int m_enemyRadius;
	int m_bossRadius;
	int m_iconRadius;

	int m_maxEnemyCount;

	int m_killPoint;
	int m_totalScore;
	int m_displayScore;
	int m_playerHitCount = 0;
	int m_totalHitCount = 0;

	int m_lastClearFrame = 0; // クリアタイム保持用
	int m_lastClearScore = 0;

	float m_startTimer = 4.0f; 
	bool m_isStarting = true;  

	bool m_GameClear = true;


	float m_imageTimer;
	float m_imageTimerLimit;


	std::mt19937 m_mt{ std::random_device{}() }; // クラス作成時に一度だけ初期化
	std::uniform_int_distribution<int> m_distX{ -610, 250 };
	//std::uniform_int_distribution<int> m_distExplosion{ -60, 60 };

	void Release();
};