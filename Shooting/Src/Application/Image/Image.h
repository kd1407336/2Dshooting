#pragma once

class C_Image
{
public:

	C_Image(){}
	~C_Image(){}

	void Draw();
	void Update();
	void Init();

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;

};