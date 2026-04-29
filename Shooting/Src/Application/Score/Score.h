#pragma once

class C_Score
{
public:
	C_Score(){}
	~C_Score(){}

	void Draw();
	void Update();
	void Init();

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	void SetScore(int score) { m_score = score; }
	int GetScore() { return m_score; }

	void SetScoreFlg(bool scoreFlg) { m_scoreFlg = scoreFlg; }
	bool GetScoreFlg() { return m_scoreFlg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

	int m_score;
	int m_scoreTimer;
	int m_timerLimit;
	int m_timerReset;

	bool m_scoreFlg;

};