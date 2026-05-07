#pragma once
#include "Application/Enemy/EnemyBase.h"

class C_BossBullet;

class C_BossEnemy	:	public C_EnemyBase
{
public:

	C_BossEnemy(){}
	~C_BossEnemy(){}

	void Draw();
	void Update();
	void Init();

	void SetAliveFlg(bool aliveFlg) { m_aliveFlg = aliveFlg; }
	bool GetAliveFlg() { return m_aliveFlg; }

	void SetHitFlg(bool hitFlg) { m_hitFlg = hitFlg; }
	bool GetHitFlg() { return m_hitFlg; }

	void SetPos(Math::Vector2 pos) { m_pos = pos; }
	Math::Vector2 GetPos() { return m_pos; }

	void Shoot(std::vector<std::unique_ptr<C_BossBullet>>& list);
	void ShootCircleStep(std::vector<std::unique_ptr<C_BossBullet>>& list);
	void Shoot3WayStep(std::vector<std::unique_ptr<C_BossBullet>>& list);
	void ShootCircle(std::vector<std::unique_ptr<C_BossBullet>>& list);

private:

	float m_currentShotAngle = 0.0f; // Œ»İ‚ÌŠp“x‚ğ•Û‘¶‚·‚é•Ï”
	int m_wayCount = 0;    // ¡A‰½”­–Ú‚ğŒ‚‚Â‚©

};