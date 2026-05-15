#pragma once

enum class KeyType 
{
	Up, Down, Left, Right
};

class C_Key
{
public:

	C_Key() {}
	~C_Key() {}

	void Draw();
	void Update();
	void Init(KeyType type);

	void SetAliveFlg(bool aliveFlg) { m_aliveFlg = aliveFlg; }
	bool GetAliveFlg() { return m_aliveFlg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_trans;
	Math::Matrix m_scale;
	KdTexture m_tex;

	float m_alpha;
	bool m_aliveFlg;

	KeyType m_type;


};
