#pragma once

class C_ClockIcon
{
public:
	C_ClockIcon() {}
	~C_ClockIcon() {}

	void Draw();
	void Update();
	void Init();

	Math::Vector2 GetPos() { return m_pos; }

	void SetAliveFlg(bool flg) { m_aliveFlg = flg; }
	bool GetAliveFlg() { return m_aliveFlg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2  m_size;
	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;

	float m_alpha;
	float m_alphaSpeed;
	float m_alphaMax;
	float m_alphaMin;
	float m_alphaReset;

	bool m_isIncreasing;

	bool m_aliveFlg;
	
};