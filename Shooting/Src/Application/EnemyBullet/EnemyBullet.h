#pragma once

class C_EnemyBullet
{
public:

	C_EnemyBullet(){}
	~C_EnemyBullet(){}

	void Draw();
	void Update();
	void Init();

	void SetAliveFlg(bool aliveFlg) { m_aliveFlg = aliveFlg; }
	bool GetAliveFlg() { return m_aliveFlg; }

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	// Velocityをセットする関数を追加
	void SetVelocity(Math::Vector2 vel) { m_velocity = vel; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;
	bool m_aliveFlg = false;

	float m_anime;
	float m_animeSpeed;
	float m_animeMax;
	float m_animeReset;

	// 1フレームあたりの移動量（方向と速さ）を保持する変数
	Math::Vector2 m_velocity = { 0.0f, 0.0f };

};