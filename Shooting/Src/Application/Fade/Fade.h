#pragma once

class C_Fade
{
public:

	C_Fade(){}
	~C_Fade(){}

	void Drwa();
	void Update();
	void Init();

	void SetFlg(bool flg) { m_flg = flg; }
	bool GetFlg() { return m_flg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;

	bool m_flg;
};