#pragma once

//class C_GameScene;

class C_Player
{
public:

	C_Player();
	~C_Player();

	void Draw();
	void Update();
	void Init();

	//生存フラグ
	void SetAliveFlg(bool flg) { m_aliveFlg = flg; }
	bool GetAliveFlg() { return m_aliveFlg; }

	//当たり判定に使用
	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	//敵と当たっているか
	void SetHitFlg(bool hitFlg) { m_hitFlg = hitFlg; }
	bool GetHitFlg() { return m_hitFlg; }


private:

	Math::Vector2 m_pos;
	Math::Vector2  m_size;
	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;

	int m_dirX;
	int m_dirY;

	//画面端当たり判定に使用
	int m_screenRight;
	int m_screenLeft;
	int m_screenTop;
	int m_screenDown;

	//HP
	float m_hp;	

	//生存フラグ
	bool m_aliveFlg;

	//ヒットフラグ
	bool m_hitFlg;

	float m_alpha;
	float m_delet;
	float m_alphaReset;

};
