#pragma once

class C_HomeIcon
{
public:
	C_HomeIcon(){}
	~C_HomeIcon(){}

	void Draw();
	void Update();
	void Init();

	void SetIconFlg(bool iconFlg) { m_iconFlg = iconFlg; }
	bool GetIconFlg() { return m_iconFlg; }

	Math::Vector2 GetPos() { return m_pos; }

private:

	Math::Vector2 m_pos;
	Math::Vector2  m_size;
	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;

	bool m_iconFlg;
	Math::Vector2 m_sizeReset;

};