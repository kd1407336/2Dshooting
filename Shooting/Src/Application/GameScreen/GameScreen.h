#pragma once

class C_GameScreen
{
public:

	C_GameScreen() {}
	~C_GameScreen() {}

	void Draw();
	void Update();
	void Init();


private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

	Math::Matrix m_screen1Mat;
	Math::Matrix m_screen1Scale;
	Math::Matrix m_screen1Trans;
};