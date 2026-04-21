#pragma once
#include "Application/Fade/FadeOut.h"

class C_FadeIn
{
public:

	C_FadeIn();
	~C_FadeIn();

	void Draw();
	void Update();
	void Init();

	void SetFlg(bool flg) { m_flg = flg; }
	bool GetFlg() { return m_flg; }

private:

	C_FadeOut m_fadeOut;

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;
	float m_alpha;
	float m_fadeSpeed;
	float m_alphaMin;
	float m_alphaReset;
	bool m_flg;

};