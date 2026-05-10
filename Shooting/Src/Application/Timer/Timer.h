#pragma once

class C_Timer
{
public:

	C_Timer(){}
	~C_Timer(){}

	void Draw();
	void Update();
	void Init();

	void MojiDraw();
	void MojiUpdate();
	void MojiInit();

	void SetTimerFlg(bool timerFlg) { m_timerFlg = timerFlg; }
	bool GetTimerFlg() { return m_timerFlg; }

	void SetClearFrame(int frame) { m_clearFrame = frame; }

	int GetTimerCnt() { return m_timerCnt; }   // 秒数（カウント数）を返す
	int GetTotalFrame() { return m_totalFrame; } // 合計フレーム数を返す

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;

	Math::Vector2 m_mojiPos;
	Math::Vector2 m_mojiSize;
	Math::Matrix m_mojiMat;
	Math::Matrix m_mojiTrans;
	Math::Matrix m_mojiScale;
	KdTexture m_mojiTex;


	int m_clearFrame;

	unsigned long m_timer;
	int m_timerLimit;
	int m_timerCnt;
	int m_timerReset;
	bool m_timerFlg;
	int m_totalFrame = 0;

};