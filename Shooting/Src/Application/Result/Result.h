#pragma once
#include "Application/State/State.h"

class C_FadeIn;
class C_FadeOut;
class C_ClockIcon;


// 演出の状態
enum class ResultStep {
	BaseScore,    // 敵を倒したスコアまで増える
	Wait,         // 少しの間（余韻）
	AddBonus,     // ボーナス分がさらに乗る
	Finish        // 完了
};

class C_ResultScene : public C_State
{
public:

	C_ResultScene(){}
	// 引数あり
	C_ResultScene(int clearFrame,int clearScore,int hitCount); 

	~C_ResultScene()override { Release(); }
	
	void Draw()override;
	void Update()override;
	void Init()override;

	void TotalTimerDraw();

	void TotalScoreDraw();
	void TotalScoreUpdate();
	void TotalScoreInit();

	void WindowDraw();
	void WindowUpdate();
	void WindowInit();

	void SetResultTime(int totalFrame) { m_resultFrame = totalFrame; }

private:

	C_FadeIn* m_fadeIn = nullptr;
	C_FadeOut* m_fadeOut = nullptr;
	C_ClockIcon* m_clockIcon = nullptr;

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

	int m_displayScore = 0;
	float m_displayTimer = 0;
	int m_resultFrame = 0; // ここにクリア時のタイムを保存する
	int m_clearScore = 0;
	int m_totalHit = 0;
	int m_baseBonus = 10000;
	int m_penaltyPerHit = 1000;
	int m_bonus = 0;

	ResultStep m_step = ResultStep::BaseScore;
	int m_waitTimer = 0; // ステップ間の待ち時間用
	float m_colorLerp = 0.0f; 

};