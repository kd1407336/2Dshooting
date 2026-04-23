#pragma once
class C_EnemyBase
{
public:

	C_EnemyBase() {}
	~C_EnemyBase() {}

	virtual void Draw();
	virtual void Update();
	virtual void Init();

protected:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;
	bool m_aliveFlg;
};
