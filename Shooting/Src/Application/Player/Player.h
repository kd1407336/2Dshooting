#pragma once

class C_Player
{
public:

	C_Player();
	~C_Player();

	void Draw();
	void Update();
	void Init();

	void SetAliveFlg(bool flg) { m_aliveFlg = flg; }
	bool GetAliveFlg() { return m_aliveFlg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2  m_size;
	KdTexture m_tex;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;

	int m_dirX;
	int m_dirY;

	int m_screenRight;
	int m_screenLeft;
	int m_screenTop;
	int m_screenDown;



	bool m_aliveFlg;

};
