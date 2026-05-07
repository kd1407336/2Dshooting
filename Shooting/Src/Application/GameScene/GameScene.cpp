#include "GameScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Enemy/Enemy.h"
#include "Application/Enemy/BossEnemy.h"
#include "Application/EnemyBullet/EnemyBullet.h"
#include "Application/EnemyBullet/BossBullet.h"
#include "Application/HomeIcon/HomeIcon.h"
#include "Application/Level/Level.h"
#include "Application/Timer/Timer.h"
#include "Application/MouseManager/MouseManager.h"

extern MouseManager g_mouse;

C_GameScene::C_GameScene()
{
	m_player = new C_Player();
	m_fadeIn = new C_FadeIn();
	m_fadeOut = new C_FadeOut();
	m_timer = new C_Timer();
	m_homeIcon = new C_HomeIcon();
	m_level = new C_Level();
	m_bEnemy = new C_BossEnemy();
}

C_GameScene::~C_GameScene()
{
	if (m_player) { delete m_player; m_player = nullptr; }
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
	if (m_timer) { delete m_timer;m_timer = nullptr; }
	if (m_homeIcon) { delete m_homeIcon; m_homeIcon = nullptr; }
	if (m_level) { delete m_level; m_level = nullptr; }
	if (m_bEnemy) { delete m_bEnemy; m_bEnemy = nullptr; }

	for (auto it = m_enemies.begin();it != m_enemies.end();)
	{
		if (!(*it)->GetAliveFlg())
		{
			it = m_enemies.erase(it);
		}
		else
		{
			it++;
		}
	}

}

void C_GameScene::Draw()
{
	//プレイヤー
	if (m_player) { m_player->Draw(); }

	for (int i = 0; i < m_scoreMax; i++)
	{
		m_score[i].Draw();
	}

	m_score[0].UiDraw(m_displayScore);

	for (auto& e : m_enemies)
	{
		e->Draw();
	}

	// 生きている弾だけ描画する
	for (auto& b : m_enemyBullets) 
	{
		if (b->GetAliveFlg()) 
		{
			b->Draw();
		}
	}

	for (auto& b : m_bossBullets)
	{
		if (b->GetAliveFlg())
		{
			b->Draw();
		}
	}


	if (m_timer) { m_timer->Draw(); }
	if (m_homeIcon) { m_homeIcon->Draw(); }
	if (m_level) { m_level->Level1Draw(); m_level->Level2Draw(); }
	if (m_bEnemy) { m_bEnemy->Draw(); }

	if (m_fadeIn) { m_fadeIn->Draw(); }
	if (m_fadeOut) { m_fadeOut->Draw(); }
}

void C_GameScene::Update()
{

	g_mouse.Update();
	Action();

	m_fadeIn->SetFlg(true);

	m_timer->SetTimerFlg(true);

	ScoreUpdate();
	HomeIconUpdate();

	//プレイヤー更新
	if (m_player) { m_player->Update(); }

	for (int i = 0; i < m_scoreMax; i++)
	{
		m_score[i].Update();
	}

	for (auto& e : m_enemies)
	{
		if (e->GetAliveFlg())
		{
			e->Update();

			e->Shoot(m_enemyBullets);
		}


	}

	for (auto& e : m_enemies) {
		if (e->IsDead()) {
			// ここで新しいXを取得してリセットする！
			float newX = GetSafeRandomX();
			e->Reset(newX, 300.0f);
		}
	}

	// 生きている弾だけ更新する
	for (auto& b : m_enemyBullets)
	{
		if (b->GetAliveFlg())
		{
			b->Update();
		}
	}

	if (m_timer) { m_timer->Update(); }
	if (m_homeIcon) { m_homeIcon->Update(); }
	if (m_level) { m_level->Level1Update(); m_level->Level2Update(); }

	// ボスの更新
	if (m_bEnemy)
	{
		m_bEnemy->Update();

		// ★重要：ここで弾の発射関数を呼ぶ！
		if (m_bEnemy->GetAliveFlg())
		{
			m_bEnemy->Shoot3WayStep(m_bossBullets);
		}

	}

	// ボス弾の移動更新
	for (auto& b : m_bossBullets)
	{
		b->Update();
	}


	if (m_totalScore >= 2000)
	{
		m_level->SetLevel2Flg(true);
		m_bEnemy->SetAliveFlg(true);
	}

	//フェードイン更新
	if (m_fadeIn->GetFlg()) { m_fadeIn->Update(); }

	//フェードアウト更新
	if (m_fadeOut->GetFlg()) { m_fadeOut->Update(); }

	//タイトルに戻る時にフェード処理を実行する
	if (m_homeIcon->GetIconFlg())
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			//タイトルに戻るときはこのフラグをtrueにする
			m_titleFadeFlg = true;

			//フェードアウト処理が始まるようにする
			m_fadeOut->SetFlg(true);
		}
	}

	if (!m_player->GetAliveFlg())
	{
		//リザルトに戻るときはこのフラグをtrueにする
		m_resultFadeFlg = true;

		//フェードアウト処理を実行する
		m_fadeOut->SetFlg(true);

	}

	//フェードアウト処理が終わっていたら
	//シーンを切り替える
	if (m_fadeOut->GetFadeFinish() && m_titleFadeFlg)
	{
		//タイトルシーンでフェードイン処理が始まるようにする
		SCENEMANAGER.SetRequestFadeIn(true);
		//タイトルシーンに戻る
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
	else if (m_fadeOut->GetFadeFinish() && m_resultFadeFlg)
	{
		//リザルトシーンでフェードイン処理が始まるようにする
		SCENEMANAGER.SetRequestFadeIn(true);

		//シーンをリザルトに切り替える
		SCENEMANAGER.ChangeState(new C_ResultScene());
	}
}

void C_GameScene::Init()
{
	if (m_player) { m_player->Init(); }
	if (m_fadeIn) { m_fadeIn->Init(); }
	if (m_fadeOut) { m_fadeOut->Init(); }
	if (m_timer) { m_timer->Init(); }
	if (m_homeIcon) { m_homeIcon->Init(); }
	if (m_level) { m_level->Level1Init(); m_level->Level2Init(); }
	if (m_bEnemy) { m_bEnemy->Init(); }

	for (int i = 0; i < m_scoreMax; i++)
	{
		m_score[i].Init();
	}

	m_enemies.clear();

	
	for (int i = 0; i < 10; i++) 
	{
		float randX = GetSafeRandomX(); // 関数を呼ぶだけ！

		auto enemy = std::make_unique<C_Enemy>();
		enemy->Init();
		// Y座標も (i * -150.0f) などでバラけさせると、ずらし沸きになります
		enemy->SetPos({ randX,300.0f });
		m_enemies.push_back(std::move(enemy));
	}


	m_enemyBullets.clear(); 
	for (int i = 0; i < m_bulletMax; i++) 
	{
		// インスタンスを生成して追加（
		auto bullet = std::make_unique<C_EnemyBullet>();
		bullet->Init();
		bullet->SetAliveFlg(false);
		m_enemyBullets.push_back(std::move(bullet));
	}


	m_bossBullets.clear();
	
	int bossBulletMax = 200;
	for (int i = 0; i < bossBulletMax; i++)
	{
		auto bullet = std::make_unique<C_BossBullet>();
		bullet->Init();
		bullet->SetAliveFlg(false);
		m_bossBullets.push_back(std::move(bullet));
	}

	//フェードフラグ初期化
	m_fadeInFlg = false;
	m_titleFadeFlg = false;
	m_resultFadeFlg = false;

	//当たり判定半径初期化
	m_radius = 50;
	m_bulletRadius = 16;
	m_charaRadius = 32;
	m_enemyRadius = 32;
	m_iconRadius = 64;

	m_maxEnemies = 10;


	//スコア初期化
	m_killPoint = 100;
	m_totalScore = 0;
	m_displayScore = 0;
}

void C_GameScene::Action()
{
	//敵とキャラの当たり判定
	for (auto& e : m_enemies)
	{
		if (!e->GetAliveFlg()) continue;

		Math::Vector2 c = e->GetPos() - m_player->GetPos();

		if (c.Length() < m_radius)
		{
			if (!m_player->GetHitFlg())
			{
				m_player->Damage();
				m_player->StartInvincible();
			}
		}

		// 弾と敵の当たり判定
		for (auto& b : m_player->GetBullets())
		{
			if (!b.active) continue;

			Math::Vector2 bc = e->GetPos() - b.pos;

			if (bc.Length() < m_bulletRadius + m_enemyRadius)
			{
				b.active = false;
				e->SetAliveFlg(false);

				m_totalScore += m_killPoint;

				// --- スコアを複数出す処理に書き換え ---
				for (auto& s : m_score) // 配列の中から探す
				{
					if (!s.GetScoreFlg())
					{
						s.SetPos(e->GetPos());   // 敵の場所に配置
						s.SetScore(m_killPoint);
						s.SetScoreFlg(true);

						break; 
					}
				}
				// --------------------------------------

				break;
			}
		}
	}

	//キャラの弾とボスの当たり判定
	for (auto& b : m_player->GetBullets())
	{
		if (!b.active) continue;

		Math::Vector2 bc = m_bEnemy->GetPos() - b.pos;

		if (bc.Length() <= 90)
		{
			b.active = false;
		}

	}



	//敵の弾とキャラの当たり判定
	for (auto& eb : m_enemyBullets)
	{
		if (!eb->GetAliveFlg()) continue;

		Math::Vector2 enemyBullet = eb->GetPos() - m_player->GetPos();

		if (enemyBullet.Length() <= m_charaRadius)
		{
			eb->SetAliveFlg(false);

			if (!m_player->GetHitFlg())
			{
				m_player->Damage();
				m_player->StartInvincible();
			}
			
		}
	}


	if (m_bEnemy->GetAliveFlg())
	{
		Math::Vector2 player = m_bEnemy->GetPos() - m_player->GetPos();

		if (player.Length() + 32)
		{
			if (!m_player->GetHitFlg())
			{
				m_player->Damage();
				m_player->StartInvincible();
			}
		}
	}

	//ボスの弾とキャラの当たり判定
	for (auto& bb : m_bossBullets)
	{
		if (!bb->GetAliveFlg()) continue;

		Math::Vector2 bossBullet = bb->GetPos() - m_player->GetPos();

		if (bossBullet.Length() <= m_charaRadius)
		{
			bb->SetAliveFlg(false);

			if(!m_player->GetHitFlg())
			{
				m_player->Damage();
				m_player->StartInvincible();
			}
			
		}

	}


}

void C_GameScene::TimerUpdate()
{

}

void C_GameScene::ScoreUpdate()
{
	if (m_displayScore < m_totalScore)
	{
		// 1. 差分を計算
		int diff = m_totalScore - m_displayScore;

		// 2. 加算量を決定（
		int addValue = diff / 20;

		// 3. 最低保証（1以下になったら1加算、または端数を処理）
		if (addValue < 1) {
			addValue = 1;
		}

		// 4. 表示用スコアを更新
		m_displayScore += addValue;
	}
}

void C_GameScene::HomeIconUpdate()
{
	Math::Vector2 homeIcon = m_homeIcon->GetPos() - g_mouse.GetPos();
	
	if (homeIcon.Length() < m_iconRadius)
	{
		m_homeIcon->SetIconFlg(true);
	}
	else
	{
		m_homeIcon->SetIconFlg(false);
	}
}

float C_GameScene::GetSafeRandomX()
{
	float randX;
	bool isOverlapping;
	const float MIN_DIST = 64.0f;
	int timeout = 0; // 無限ループ防止用

	do {
		isOverlapping = false;
		randX = (float)m_distX(m_mt); // メンバ変数のエンジンを使う

		for (const auto& e : m_enemies) {
			// e が自分自身でないか、かつ生きている敵と重なっていないか
			if (!e->IsDead() && std::abs(randX - e->GetPos().x) < MIN_DIST) {
				isOverlapping = true;
				break;
			}
		}

		// 万が一、どこにも置けない場合にフリーズするのを防ぐ
		timeout++;
		if (timeout > 100) break;

	} while (isOverlapping);

	return randX;
}
