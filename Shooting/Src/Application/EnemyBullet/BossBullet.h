#pragma once

class C_BossBullet
{
public:

	C_BossBullet() {}
	~C_BossBullet() {}

	void Draw();
	void Update();
	void Init();

	void SetAliveFlg(bool aliveFlg) { m_aliveFlg = aliveFlg; }
	bool GetAliveFlg() { return m_aliveFlg; }

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	void SetVelocity(Math::Vector2 vel) { m_velocity = vel; }

private:
	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Vector2 m_velocity;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

	float m_anime;
	float m_animeSpeed;
	float m_animeMax;
	float m_animeReset;

	bool m_aliveFlg = false;
};