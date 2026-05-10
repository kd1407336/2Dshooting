#include "GameScene.h"
#include "Application/SceneManager/SceneManager.h"
#include "Application/Fade/FadeOut.h"
#include "Application/GameScreen/GameScreen.h"
#include "Application/GameClear/GameClear.h"
#include "Application/GameOver/GameOver.h"
#include "Application/Enemy/BossEnemy.h"
#include "Application/HomeIcon/HomeIcon.h"
#include "Application/Level/Level.h"
#include "Application/Timer/Timer.h"
#include "Application/MouseManager/MouseManager.h"
#include "Application/Window/Window.h"


extern MouseManager g_mouse;


void C_GameScene::Draw()
{
	if (m_gameScreen) { m_gameScreen->Draw(); }
	if (m_window) { m_window->Draw(); }

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
	if (m_level) 
	{
		m_level->Level1Draw(); 
		m_level->Level2Draw();

		if(m_level->GetLevel3Flg())
		{
			m_level->Level3Draw();
		}
		m_level->LevelMaxDraw();
	}
	if (m_bEnemy) { m_bEnemy->Draw(); }
	if (m_gameClear) { m_gameClear->Draw(); }
	if (m_gameOver) { m_gameOver->Draw(); }

	for (auto& ex : m_explosions)
	{
		ex->Draw();
	}

	if (m_fadeIn) { m_fadeIn->Draw(); }
	if (m_fadeOut) { m_fadeOut->Draw(); }
}

void C_GameScene::Update()
{


	g_mouse.Update();
	Action();

	m_fadeIn->SetFlg(true);


	ScoreUpdate();
	HomeIconUpdate();

	//プレイヤー更新
	if (m_player) { m_player->Update(); }

	for (int i = 0; i < m_scoreMax; i++)
	{
		m_score[i].Update();
	}

	if (m_bEnemy && !m_bEnemy->GetAliveFlg())
	{
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
				e->Reset(newX, 380.0f);
			}
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

	// Update内
	for (auto& ex : m_explosions)
	{
		ex->Update();
	}

	if (m_gameScreen) { m_gameScreen->Update(); }
	if (m_timer) { m_timer->Update(); }
	if (m_homeIcon) { m_homeIcon->Update(); }
	if (m_level) 
	{ 
	m_level->Level1Update(); 
	m_level->Level2Update();
	m_level->Level3Update();
	m_level->LevelMaxUpdate();
	}
	if (m_window) { m_window->Update(); }
	if (m_gameClear) { m_gameClear->Update(); }
	if (m_gameOver) { m_gameOver->Update(); }


	// ボスの更新
	if (m_bEnemy && m_bEnemy->GetAliveFlg())
	{
		m_bEnemy->Update();

		// 現在のHP割合を計算（1.0 = 満タン, 0.5 = 半分）
		float hpRate = m_bEnemy->GetHp() / m_bEnemy->GetHpMax();

		if (hpRate > 0.7f)
		{
			// 体力 70% 以上の時：通常の3方向ショット
			m_bEnemy->Shoot3WayStep(m_bossBullets);
		}
		else if (hpRate > 0.3f)
		{
			// 体力 30% ～ 70% の時：円形ショット
			m_bEnemy->ShootCircleStep(m_bossBullets);
		}
		else
		{
			// 体力 30% 未満の時：もっと激しい攻撃（例：両方を同時に呼ぶなど）
			m_bEnemy->Shoot3WayStep(m_bossBullets);
			m_bEnemy->ShootCircleStep(m_bossBullets);
		}

	}

	if(m_bEnemy->GetAliveFlg())
	{
		// ボス弾の移動更新
		for (auto& b : m_bossBullets)
		{
			b->Update();
		}
	}

	if (m_bEnemy->GetHp() <= 0)
	{
		// ★ここでボスの弾をすべて消す！
		for (auto& b : m_bossBullets)
		{
			b->SetAliveFlg(false);
		}
	}

	// Level 2
	if (m_totalScore >= 2000 && !m_level->GetLevel2Flg())
	{
		m_level->SetLevel2Flg(true);
	}

	// Level 3
	// 「!m_level->GetLevel3Flg()」を入れて、一度だけtrueにするようにします
	if (m_totalScore >= 5000)
	{
		m_level->SetLevel3Flg(true);
	}

	// Level Max
	if (m_totalScore >= 9000)
	{
		m_level->SetLevelMaxFlg(true);

		if (m_bEnemy) {
			m_bEnemy->SetAliveFlg(true);
			// 必要ならここでボスのHPをフルにするなどの初期化
		}

		// 雑魚と弾の一掃
		for (auto& e : m_enemies) { e->SetAliveFlg(false); }
		for (auto& b : m_enemyBullets) { b->SetAliveFlg(false); }
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



	if (GetAsyncKeyState('K') & 0x8000 && !m_isGameOver)
	{
		m_player->SetHp(0);
		m_isGameOver = true;
	}

	if (GetAsyncKeyState('B') & 0x8000 && !m_isGameClear)
	{
		m_bEnemy->SetHp(0);
		m_isGameClear = true;
	}


	if (m_bEnemy->GetHp() <= 0)
	{
		m_bEnemy->SetAliveFlg(false);
		m_isGameClear = true;
	}

	// --- ゲームオーバー中の処理 ---
	if (m_isGameOver)
	{
		m_gameOver->SetAliveFlg(true);

		m_gameOverTimer--;

		// タイマーが 0 になった瞬間に一度だけ実行
		if (m_gameOverTimer <= 0)
		{
			// 既にフェードアウトが始まっていないか確認（二重処理防止）
			if (m_fadeOut && !m_fadeOut->GetFlg())
			{
				// 遷移用のデータを確定させる
				if (m_timer) {
					m_timer->SetTimerFlg(false);
					m_lastClearFrame = m_timer->GetTotalFrame();
				}

				// 0除算防止（念のためのガード）
				if (m_lastClearFrame <= 0) m_lastClearFrame = 1;

				m_lastClearScore = m_totalScore;
				m_totalHitCount = m_playerHitCount;

				// リザルト遷移フラグを立ててフェード開始
				m_resultFadeFlg = true;
				m_fadeOut->SetFlg(true);
			}
		}
	}

	// --- ゲームクリアー中の処理 ---
	if (m_isGameClear)
	{
		m_gameClear->SetAliveFlg(true);

		m_gameClearTimer--;

		// タイマーが 0 になった瞬間に一度だけ実行
		if (m_gameClearTimer <= 0)
		{
			if (m_fadeOut && !m_fadeOut->GetFlg())
			{
				if (m_timer) {
					m_timer->SetTimerFlg(false);
					m_lastClearFrame = m_timer->GetTotalFrame();
				}

				if (m_lastClearFrame <= 0) m_lastClearFrame = 1;

				m_lastClearScore = m_totalScore;
				m_totalHitCount = m_playerHitCount;

				m_resultFadeFlg = true;
				m_fadeOut->SetFlg(true);
			}
		}
	}



	// 1. Rキーが押されているかチェック
	if (GetAsyncKeyState('R') & 0x8000)
	{
		// 1. タイマーを停止
		m_timer->SetTimerFlg(false);

		// ★フェード開始前に今のタイムをメモしておく
		m_lastClearFrame = m_timer->GetTotalFrame();

		m_lastClearScore = m_totalScore;

		m_totalHitCount = m_playerHitCount;



		//リザルトに戻るときはこのフラグをtrueにする
		m_resultFadeFlg = true;

		//フェードアウト処理を実行する
		m_fadeOut->SetFlg(true);
		//// 3. リザルトシーンへ値を渡す
		//// ※ pResultScene は ResultScene のインスタンスへのポインタと仮定
		//pResultScene->SetResultTime(s
	}
	else
	{
		// Rキーを押していない間：常にタイマーを動かす
		m_timer->SetTimerFlg(true);
	}

	if (!m_player->GetAliveFlg())
	{
		////リザルトに戻るときはこのフラグをtrueにする
		//m_resultFadeFlg = true;

		////フェードアウト処理を実行する
		//m_fadeOut->SetFlg(true);

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
		SCENEMANAGER.ChangeState(new C_ResultScene(m_lastClearFrame, m_lastClearScore, m_totalHitCount));
	}
}

void C_GameScene::Init()
{

	m_player = new C_Player();
	m_fadeIn = new C_FadeIn();
	m_fadeOut = new C_FadeOut();
	m_gameScreen = new C_GameScreen();
	m_gameClear = new C_GameClear();
	m_gameOver = new C_GameOver();
	m_timer = new C_Timer();
	m_homeIcon = new C_HomeIcon();
	m_level = new C_Level();
	m_bEnemy = new C_BossEnemy();
	m_window = new C_Window();

	if (m_player) { m_player->Init(); }
	if (m_fadeIn) { m_fadeIn->Init(); }
	if (m_fadeOut) { m_fadeOut->Init(); }
	if (m_gameScreen) { m_gameScreen->Init(); }
	if (m_timer) { m_timer->Init(); }
	if (m_homeIcon) { m_homeIcon->Init(); }
	if (m_level)
	{
		m_level->Level1Init();
		m_level->Level2Init();
		m_level->Level3Init();
		m_level->LevelMaxInit();
	}
	if (m_bEnemy) { m_bEnemy->Init(); }
	if (m_window) { m_window->Init(); }
	if (m_gameClear) { m_gameClear->Init(); }
	if (m_gameOver) { m_gameOver->Init(); }

	for (int i = 0; i < m_explosionMax; i++)
	{
		m_explosions.push_back(std::make_unique<C_Explosion>());
		m_explosions.back()->Init();
	}

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
	m_isGameOver = false;
	m_isGameClear = false;

	//当たり判定半径初期化
	m_radius = 50;
	m_bulletRadius = 16;
	m_charaRadius = 32;
	m_enemyRadius = 32;
	m_bossRadius = 90;
	m_iconRadius = 64;

	m_maxEnemies = 10;

	m_gameOverTimer = 360;
	m_gameClearTimer = 360;

	//スコア初期化
	m_killPoint = 200;
	m_totalScore = 0;
	m_displayScore = 0;
}

void C_GameScene::Action()
{
	//敵とキャラの当たり判定===================================================
	for (auto& e : m_enemies)
	{
		if (!e->GetAliveFlg()) continue;

		Math::Vector2 c = e->GetPos() - m_player->GetPos();

		if (c.Length() < m_radius)
		{
			if (!m_player->GetHitFlg())
			{
				m_player->Damage();
				m_playerHitCount++;
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

				// --- 爆発をリストから探して再生 ---
				for (auto& ex : m_explosions)
				{
					if (!ex->GetAliveFlg()) // 空いている爆発エフェクトを探す
					{
						ex->SetPos(e->GetPos());   // 敵の場所に配置
						ex->SetAliveFlg(true);     // 再生開始！
						// ※必要ならここでアニメーションフレーム(m_anime)を 0 にリセットする関数を呼ぶ
						break;
					}
				}

				// --- スコアを複数出す処理に書き換え ---
				for (auto& s : m_score) // 配列の中から探す
				{
					if (!s.GetScoreFlg())
					{
						// 敵の座標を取得
						Math::Vector2 enemyPos = e->GetPos();

						// ★座標を少し上にずらす (Y座標にプラス、または環境によってはマイナス)
						// 一般的な2Dゲームの座標系（上がプラス）なら +30.0f くらい
						enemyPos.x += 30.0f;
						enemyPos.y -= 20.0f;

						s.SetPos(enemyPos);      // ずらした位置に配置
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
	//==============================================================================

	//敵の弾とキャラの当たり判定=======================================================
	for (auto& eb : m_enemyBullets)
	{
		if (!eb->GetAliveFlg()) continue;

		Math::Vector2 enemyBullet = m_player->GetPos() - eb->GetPos();

		if(eb->GetAliveFlg())
		{
			if (enemyBullet.Length() <= m_charaRadius)
			{
				eb->SetAliveFlg(false);

				if (!m_player->GetHitFlg())
				{
					m_player->Damage();
					m_playerHitCount++;   
					m_player->StartInvincible();
				}
			}
		}
	}
	//===================================================================================

	// 敵の弾とプレイヤーの弾の当たり判定
	for (auto& eb : m_enemyBullets)
	{
		// そもそも敵の弾が生きていないなら判定スキップ
		if (!eb->GetAliveFlg()) continue;

		for (auto& pb : m_player->GetBullets())
		{
			// プレイヤーの弾が生きていないなら判定スキップ
			if (!pb.active) continue;

			// 弾と弾の間のベクトルを計算
			Math::Vector2 diff = eb->GetPos() - pb.pos;

			if (diff.Length() < 32.0f)
			{

				// --- 爆発をリストから探して再生 ---
				for (auto& ex : m_explosions)
				{
					if (!ex->GetAliveFlg()) // 空いている爆発エフェクトを探す
					{
						ex->SetPos(eb->GetPos());   // 敵の場所に配置
						ex->SetAliveFlg(true);     // 再生開始！
						
						break;
					}
				}

				pb.active = false;      // プレイヤーの弾を消す
				eb->SetAliveFlg(false); // 敵の弾を消す
				break;                  // 敵の弾ebは消えたので、次の敵弾のループへ
			}
		}
	}

	if(m_bEnemy->GetAliveFlg())
	{
		// --- ボスの弾とプレイヤーの弾の当たり判定 ---
		for (auto& bb : m_bossBullets) // bb = Boss Bullet
		{
			if (!bb->GetAliveFlg()) continue;

			for (auto& pb : m_player->GetBullets())
			{
				if (!pb.active) continue;

				Math::Vector2 diff = bb->GetPos() - pb.pos;

				if (diff.Length() < 32.0f)
				{
					pb.active = false;      // プレイヤーの弾を消す
					bb->SetAliveFlg(false); // ボスの弾を消す

					// --- 爆発をリストから探して再生 ---
					for (auto& ex : m_explosions)
					{
						if (!ex->GetAliveFlg()) // 空いている爆発エフェクトを探す
						{
							ex->SetPos(bb->GetPos());   // 敵の場所に配置
							ex->SetAliveFlg(true);     // 再生開始！

							break;
						}
					}
					// ★ここに爆発エフェクトを出す処理を追加してもOK！

					break;
				}
			}
		}
	}


	//キャラの弾とボスの当たり判定==================================================
	for (auto& b : m_player->GetBullets())
	{
		if (!b.active) continue;

		Math::Vector2 bc = m_bEnemy->GetPos() - b.pos;

		if (m_bEnemy->GetAliveFlg())
		{
			if (bc.Length() <= m_bossRadius)
			{
				b.active = false;

				if (!m_bEnemy->GetHitFlg())
				{
					m_bEnemy->Damage();
				}

				// --- 爆発をリストから探して再生 ---
				for (auto& ex : m_explosions)
				{
					if (!ex->GetAliveFlg()) // 空いている爆発エフェクトを探す
					{
						// 1. ボスの現在位置を取得
						Math::Vector2 bossPos = m_bEnemy->GetPos();

						// 2. 下方向へのオフセット（ずらす量）を設定 (例: 30.0f)
						// ※値はボスの画像サイズや爆発エフェクトの大きさに合わせて調整してください。
						float offsetY = 45.0f;

						// 3. Y座標を調整してセット（一般的な2D座標系ではYを引くと下になります）
						ex->SetPos({ bossPos.x, bossPos.y - offsetY });
						// ---------------
						ex->SetAliveFlg(true);     // 再生開始！

						break;
					}
				}


			}
		}

	}
	//================================================================================


	//ボスとキャラの当たり判定===========================================================
	if (m_bEnemy->GetAliveFlg())
	{
		Math::Vector2 player = m_player->GetPos() - m_bEnemy->GetPos();

		if (player.Length() <= m_charaRadius + m_bossRadius)
		{
			if (!m_player->GetHitFlg())
			{
				m_player->Damage();
				m_playerHitCount++;      // ヒット数をプラス
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
				m_playerHitCount++;      // ヒット数をプラス
				m_player->StartInvincible();
			}
			
		}

	}
	//==========================================================================================

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

void C_GameScene::Release()
{
	if (m_player) { delete m_player; m_player = nullptr; }
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
	if (m_gameScreen) { delete m_gameScreen; m_gameScreen = nullptr; }
	if (m_gameClear) { delete m_gameClear; m_gameClear = nullptr; }
	if (m_gameOver) { delete m_gameOver; m_gameOver = nullptr; }
	if (m_timer) { delete m_timer;m_timer = nullptr; }
	if (m_homeIcon) { delete m_homeIcon; m_homeIcon = nullptr; }
	if (m_level) { delete m_level; m_level = nullptr; }
	if (m_bEnemy) { delete m_bEnemy; m_bEnemy = nullptr; }
	if (m_window) { delete m_window; m_window = nullptr; }


	/*for (auto it = m_enemies.begin();it != m_enemies.end();)
	{
		if (!(*it)->GetAliveFlg())
		{
			it = m_enemies.erase(it);
		}
		else
		{
			it++;
		}
	}*/
	m_enemies.clear();
	m_enemyBullets.clear();
	m_bossBullets.clear();
	m_explosions.clear(); // 爆発エフェクトも同様
}
