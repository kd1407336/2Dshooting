#pragma once

class C_FadeOut
{
public:

	C_FadeOut();
	~C_FadeOut();

	void Draw();
	void Update();
	void Init();

	void SetFlg(bool flg) { m_flg = flg; }
	bool GetFlg() { return m_flg; }

	bool GetFadeFinish() { return m_fadeFinish; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;
	float m_alpha;
	float m_fadeSpeed;
	float m_alphaMax;
	float m_alphaReset;
	bool m_flg;
	bool m_fadeFinish;

};