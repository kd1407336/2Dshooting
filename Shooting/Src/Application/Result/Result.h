#pragma once
#include "Application/State/State.h"

class C_FadeIn;
class C_FadeOut;
class C_ClockIcon;
class C_ResultLogo;

// 演出の状態
enum class ResultStep 
{
	
	BaseScore,      // 基本スコア表示
	WaitHit,        // 被弾ボーナス前の待ち
	AddHitBonus,    // 被弾ボーナスを表示
	WaitTime,       // タイムボーナス合算前の待ち
	AddTimeBonus,   // タイムボーナスを合算
	Finish          // メインスコアへ加算開始

};

class C_ResultScene : public C_State
{
public:

	C_ResultScene(){}
	// 引数あり
	C_ResultScene(int clearFrame,int clearScore,int hitCount, bool isClear);

	~C_ResultScene()override { Release(); }
	
	void Draw()override;
	void Update()override;
	void Init()override;

	void TotalTimerDraw();
	void TotalTimerUpdate();

	void TotalScoreDraw();
	void TotalScoreUpdate();
	void TotalScoreInit();

	void WindowDraw();
	void WindowUpdate();
	void WindowInit();

	void ScoreDraw();
	void ScoreUpdate();
	void ScoreInit();

	void SetResultTime(int totalFrame) { m_resultFrame = totalFrame; }

private:

	C_FadeIn* m_fadeIn = nullptr;
	C_FadeOut* m_fadeOut = nullptr;
	C_ClockIcon* m_clockIcon = nullptr;
	C_ResultLogo* m_resultLogo = nullptr; 

	void Release();

	Math::Vector2 m_scorePos;
	Math::Vector2 m_scoreSize;
	Math::Matrix m_scoreMat;
	Math::Matrix m_scoreTrans;
	Math::Matrix m_scoreScale;
	KdTexture m_scoreTex;

	Math::Vector2 m_windowPos;
	Math::Vector2 m_windowSize;
	Math::Matrix m_windowMat;
	Math::Matrix m_windowScale;
	Math::Matrix m_windowTrans;
	KdTexture m_windowTex;


	//スコア文字用
	Math::Vector2 m_scoreMojiPos;
	Math::Vector2 m_scoreMojiSize;
	Math::Matrix m_scoreMojiMat;
	Math::Matrix m_scoreMojiTrans;
	Math::Matrix m_scoreMojiScale;
	KdTexture m_scoreMojiTex;

	int m_displayScore = 0;
	float m_displayTimer = 0;
	
	int m_clearScore = 0;
	int m_totalHit = 0;
	int m_baseBonus = 10000;
	int m_penaltyPerHit = 1000;
	int m_bonus = 0;


	int m_resultFrame = 0; // ここにクリア時のタイムを保存する
	int m_baseTimerBonus = 10000;
	int m_timerBonus = 0;
	
	int m_currentBonusDisplay = 0; // 右側に表示するボーナス合算値用

	ResultStep m_step = ResultStep::BaseScore;
	int m_waitTimer = 0; // ステップ間の待ち時間用
	float m_colorLerp = 0.0f; 

	KdTexture m_resultLogoTex; 
	bool      m_isClear;       // 判定保持用

};