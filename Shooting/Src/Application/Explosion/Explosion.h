#pragma once

class C_Explosion
{
public:

	C_Explosion(){}
	~C_Explosion(){}

	void Draw();
	void Update();
	void Init();

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	void SetAliveFlg(bool aliveFlg) { m_aliveFlg = aliveFlg; }
	bool GetAliveFlg() { return m_aliveFlg; }


private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

	static constexpr float m_animeSpeed = 0.3f;       // アニメーションの再生速度
	static constexpr float m_maxAnimeFrame = 8.0f; // アニメーションの総枚数
	float m_anime;
	bool m_aliveFlg;

};
