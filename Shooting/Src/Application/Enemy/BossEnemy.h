#pragma once
#include "Application/Enemy/EnemyBase.h"

class C_BossBullet;

enum class BossState 
{
	Appear, // 画面外から登場中
	Move    // 画面内で行動中
};


class C_BossEnemy	:	public C_EnemyBase
{
public:

	C_BossEnemy(){}
	~C_BossEnemy(){}

	void Draw();
	void Update();
	void Init();

	void HpDraw();
	void HpUpdate();
	void HpInit();


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
	void C_BossEnemy::ShootAimNWay(std::vector<std::unique_ptr<C_BossBullet>>& list, Math::Vector2 playerPos);



	void SetHp(float hp) { m_hp = hp; }
	float GetHp() { return m_hp; }
	float GetHpMax() { return m_hpMax; }

	void Damage();

private:

	//HP用
	Math::Vector2 m_hpPos;
	Math::Vector2 m_hpSize;
	Math::Matrix m_hpMat;
	Math::Matrix m_hpTrans;
	Math::Matrix m_hpScale;
	KdTexture m_hpTex;

	Math::Vector2 m_hpBerPos;
	Math::Vector2 m_hpBerSize;
	Math::Matrix m_hpBerMat;
	Math::Matrix m_hpBerTrans;
	Math::Matrix m_hpBerScale;
	Math::Matrix m_hpDrawMat;


	Math::Vector2 m_mojiPos;
	Math::Vector2 m_mojiSize;
	Math::Matrix m_mojiMat;
	Math::Matrix m_mojiTrans;
	Math::Matrix m_mojiScale;
	KdTexture m_mojiTex;

	// --- ボスHPバーの左に表示する「BOSS」ロゴ用 ---
	Math::Vector2 m_bossLogoPos;
	Math::Vector2 m_bossLogoSize;
	Math::Matrix  m_bossLogoScaleMat; // 変数名をより明確に
	Math::Matrix  m_bossLogoTransMat; // 変数名をより明確に
	Math::Matrix  m_bossLogoMat;      // 最終的な合成行列
	KdTexture     m_bossLogoTex;

	float m_hp;
	float m_hpMax;
	float m_hpDraw;

	float m_currentShotAngle = 0.0f; // 現在の角度を保存する変数
	int m_wayCount = 0;    // 今、何発目を撃つか


	BossState m_state = BossState::Appear;
	float m_moveTimer = 0.0f; // 移動演出用のタイマー

};