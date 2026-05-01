#pragma once

class C_State
{
public:

	C_State();
	virtual ~C_State();

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Init() = 0;

	virtual void Action();
	virtual void TimerUpdate();
	virtual void ScoreUpdate();

protected:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

};