#include "GameScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/Enemy/Enemy.h"
#include "Application/Timer/Timer.h"

C_GameScene::C_GameScene()
{
	m_player = new C_Player();
	m_fadeIn = new C_FadeIn();
	m_fadeOut = new C_FadeOut();
	m_timer = new C_Timer();
}

C_GameScene::~C_GameScene()
{
	if (m_player) { delete m_player; m_player = nullptr; }
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
	if (m_timer) { delete m_timer;m_timer = nullptr; }

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

	if (m_timer) { m_timer->Draw(); }

	if (m_fadeIn) { m_fadeIn->Draw(); }
	if (m_fadeOut) { m_fadeOut->Draw(); }
}

void C_GameScene::Update()
{
	Action();

	m_fadeIn->SetFlg(true);

	m_timer->SetTimerFlg(true);

	ScoreUpdate();

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
		}
	}

	/*std::random_device rand;
	std::mt19937 mt(rand);
	std::uniform_int_distribution<int>enemy(2,100);*/

	if (m_timer) { m_timer->Update(); }

	
	//フェードイン更新
	if(m_fadeIn->GetFlg()){m_fadeIn->Update();}

	//フェードアウト更新
	if (m_fadeOut->GetFlg()) { m_fadeOut->Update(); }

	//タイトルに戻る時にフェード処理を実行する
	if (GetAsyncKeyState('T') & 0x8000)
	{
		//タイトルに戻るときはこのフラグをtrueにする
		m_titleFadeFlg = true;

		//フェードアウト処理が始まるようにする
		m_fadeOut->SetFlg(true);
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
	if (m_fadeOut->GetFadeFinish()&& m_titleFadeFlg)		
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

	for (int i = 0; i < m_scoreMax; i++)
	{
		m_score[i].Init();
	}

	m_enemies.clear();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distX(-610, 610);

	const float MIN_DIST = 64.0f; 

	for (int i = 0; i < 10; i++)
	{
		float randX;
		bool isOverlapping;

		// --- 重ならない場所が見つかるまでループ ---
		do {
			isOverlapping = false;
			randX = (float)distX(mt);

			// すでにリストにいる敵と順番に比較
			for (const auto& e : m_enemies) {
				if (std::abs(randX - e->GetPos().x) < MIN_DIST) {
					isOverlapping = true; 
					break;
				}
			}
		} while (isOverlapping);
		// ---------------------------------------

		auto enemy = std::make_unique<C_Enemy>();
		enemy->Init();
		enemy->SetPos({ randX, 200.0f });
		m_enemies.push_back(std::move(enemy));
	}

	//フェードフラグ初期化
	m_fadeInFlg = false;
	m_titleFadeFlg = false;
	m_resultFadeFlg = false;

	//当たり判定半径初期化
	m_radius = 50;
	m_bulletRadius = 16;
	m_enemyRadius = 32;

	m_maxEnemies = 10;

	//スコア初期化
	m_killPoint = 100;
	m_totalScore = 0;
	m_displayScore = 0;
}

void C_GameScene::Action()
{
	for (auto& e : m_enemies)
	{
		if (!e->GetAliveFlg()) continue;

		// プレイヤーと敵の当たり判定
	/*	float dx = m_player->GetPos().x - e->GetPos().x;
		float dy = m_player->GetPos().y - e->GetPos().y;
		float c = sqrt(dx * dx + dy * dy);*/

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

			/*float bx = b.pos.x - e->GetPos().x;
			float by = b.pos.y - e->GetPos().y;
			float bc = sqrt(bx * bx + by * by);*/

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
