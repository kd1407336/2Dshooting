#pragma once
#include "EnemyBase.h"

class C_Enemy : public C_EnemyBase
{
public:

	C_Enemy(){}
	~C_Enemy(){}

	void Draw()override;
	void Update()override;
	void Init()override;

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

private:

	
};