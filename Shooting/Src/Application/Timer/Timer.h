#pragma once

class C_Timer
{
public:

	C_Timer(){}
	~C_Timer(){}

	void Draw();
	void Update();
	void Init();


private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;


};