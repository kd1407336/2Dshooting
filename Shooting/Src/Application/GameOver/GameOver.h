#pragma once

class C_GameOver
{
public:
	C_GameOver(){}
	~C_GameOver() {}

	void Draw();
	void Update();
	void Init();

	void SetAliveFlg(bool aliveFlg) { m_aliveFlg = aliveFlg; }
	bool GetAliveFlg() { return m_aliveFlg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;
	float m_alpha;
	float m_alphaMax;
	float m_alphaSpeed;
	bool m_aliveFlg;
};