#pragma once

class C_Score
{
public:
	C_Score(){}
	~C_Score(){}

	void Draw();
	void Update();
	void Init();

	void UiDraw(int _totalScore);
	void UiUpdate();
	void UiInit();

	void ScoreDraw();
	void ScoreUpdate();
	void ScoreInit();

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	void SetScore(int score) { m_score = score; }
	int GetScore() { return m_score; }

	void SetScoreFlg(bool scoreFlg) { m_scoreFlg = scoreFlg; }
	bool GetScoreFlg() { return m_scoreFlg; }

private:

	//エフェクト用UI
	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

	//スコア合計値用UI
	Math::Vector2 m_uiPos; 
	Math::Vector2 m_uiSize;
	Math::Matrix  m_uiScaleMat;
	Math::Matrix  m_uiTransMat;
	Math::Matrix  m_uiMat;
	float         m_uiAlpha;  

	//スコア文字用
	Math::Vector2 m_scorePos;
	Math::Vector2 m_scoreSize;
	Math::Matrix m_scoreMat;
	Math::Matrix m_scoreTrans;
	Math::Matrix m_scoreScale;
	KdTexture m_scoreTex;

	unsigned long m_score;
	int m_scoreTimer;
	int m_timerLimit;
	int m_timerReset;
	float m_alpha;
	float m_alphaReset;

	float m_upSpeed;

	bool m_scoreFlg;

};