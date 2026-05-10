#pragma once

class C_Window
{
public:

	C_Window(){}

	~C_Window(){}

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
};