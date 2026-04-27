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
	void Action();

	void HpDraw();
	void HpUpdate();
	void HpInit();

	void BulletDraw();
	void BulletUpdate();
	void BulletInit();

	//生存フラグ
	void SetAliveFlg(bool flg) { m_aliveFlg = flg; }
	bool GetAliveFlg() { return m_aliveFlg; }

	//当たり判定に使用
	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	//敵と当たっているか
	void SetHitFlg(bool hitFlg) { m_hitFlg = hitFlg; }
	bool GetHitFlg() { return m_hitFlg; }

	void SetHitOnFlg(bool hitOnFlg) { m_hitOnFlg = hitOnFlg; }
	bool GetHitOnFlg() { return m_hitOnFlg; }

	Math::Vector2 GetBulletPos() { return m_pos; }

private:

	//キャラ用
	Math::Vector2 m_pos;
	Math::Vector2  m_size;
	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;

	//HP用
	Math::Vector2 m_hpPos;
	Math::Vector2 m_hpSize;
	Math::Matrix m_hpMat;
	Math::Matrix m_hpTrans;
	Math::Matrix m_hpScale;
	KdTexture m_hpTex;

	//弾用
	Math::Vector2 m_bulletPos;
	Math::Vector2 m_bulletSize;
	Math::Matrix m_bulletMat;
	Math::Matrix m_bulletTrans;
	Math::Matrix m_bulletScale;
	KdTexture m_bulletTex;
	bool m_bulletFlg = false;

	int m_dirX;
	int m_dirY;

	//画面端当たり判定に使用
	int m_screenRight;
	int m_screenLeft;
	int m_screenTop;
	int m_screenDown;

	//HP
	float m_hp;	
	float m_hpMax;
	float m_hpDraw;

	//生存フラグ
	bool m_aliveFlg;

	//ヒットフラグ
	bool m_hitFlg;
	bool m_hitOnFlg;

	//アルファー値========
	float m_alpha;
	float m_alphaMax;
	float m_alphaMin;
	float m_delet;
	float m_alphaReset;
	//====================

	int m_charaRadius;

	


};
