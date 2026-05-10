#pragma once

//class C_GameScene;

struct Bullet
{
	Math::Vector2 pos;
	bool active = true;
};

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

	void MojiDraw();
	void MojiUpdate();
	void MojiInit();

	//生存フラグ
	void SetAliveFlg(bool flg) { m_aliveFlg = flg; }
	bool GetAliveFlg() { return m_aliveFlg; }

	//当たり判定に使用
	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	//敵と当たっているか
	void SetHitFlg(bool hitFlg) { m_hitFlg = hitFlg; }
	bool GetHitFlg() { return m_hitFlg; }

	void Damage();

	void SetHp(int hp) { m_hp = hp; }
	int GetHp() { return m_hp; }

	Math::Vector2 GetBulletPos() { return m_bulletPos; }

	std::vector<Bullet>& C_Player::GetBullets(){return m_bullets;}

	void StartInvincible();

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

	Math::Vector2 m_hpBerPos;
	Math::Vector2 m_hpBerSize;
	Math::Matrix m_hpBerMat;
	Math::Matrix m_hpBerTrans;
	Math::Matrix m_hpBerScale;
	Math::Matrix m_hpDrawMat;

	//弾用
	Math::Vector2 m_bulletPos;
	Math::Vector2 m_bulletSize;
	Math::Matrix m_bulletMat;
	Math::Matrix m_bulletTrans;
	Math::Matrix m_bulletScale;
	KdTexture m_bulletTex;
	bool m_bulletFlg = false;
	int m_shotInterval;
	int m_shotIntervalMax;

	Math::Vector2 m_mojiPos;
	Math::Vector2 m_mojiSize;
	Math::Matrix m_mojiMat;
	Math::Matrix m_mojiTrans;
	Math::Matrix m_mojiScale;
	KdTexture m_mojiTex;

	std::vector<Bullet> m_bullets;

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
	float m_anime;
	float m_animeSpeed;
	float m_animeMax;
	float m_animeMin;
	float m_animeReset;
	
	float m_invincibleTime;
	float m_invincibleMax;


};
