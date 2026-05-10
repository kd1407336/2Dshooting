#include "Result.h"
#include "../Fade/FadeIn.h"
#include "../Fade/FadeOut.h"
#include "Application/ClockIcon/ClockIcon.h"
#include "Application/SceneManager/SceneManager.h"

C_ResultScene::C_ResultScene(int clearFrame,int clearScore,int hitCount)
	  : m_resultFrame(clearFrame),
		m_clearScore(clearScore),
		m_totalHit(hitCount)
{
	// ここには画像ロードなどの処理を書く
}

void C_ResultScene::Draw()
{
	WindowDraw();
	TotalTimerDraw();
	TotalScoreDraw();
	

	if (m_clockIcon) { m_clockIcon->Draw(); }

	if(m_fadeIn){m_fadeIn->Draw();}
	if(m_fadeOut){m_fadeOut->Draw();}
	
}

void C_ResultScene::Update()
{
	if (m_clockIcon) { m_clockIcon->Update(); m_clockIcon->SetAliveFlg(true); }
	if (m_fadeIn) { m_fadeIn->Update(); }
	if (m_fadeOut) { m_fadeOut->Update(); }

	TotalScoreUpdate();
	WindowUpdate();

	if (SCENEMANAGER.GetRequestFadeIn())
	{
		m_fadeIn->SetFlg(true);
	}

	//タイトルシーンに戻る
	if (GetAsyncKeyState('T') & 0x8000)
	{
		m_fadeOut->SetFlg(true);
	}

	if (m_fadeOut->GetFadeFinish())
	{
		//タイトルシーンでフェードイン処理が始まるようにする
		SCENEMANAGER.SetRequestFadeIn(true);

		SCENEMANAGER.ChangeState(new C_TitleScene());
	}

	

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scale = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_mat = m_scale * m_trans;
}

void C_ResultScene::Init()
{
	m_pos = { 0,200 };
	m_size = { 2.0f,2.0f };
	m_tex.Load("Texture/Score/Suuji.png");

	m_clockIcon = new C_ClockIcon();
	if (m_clockIcon) { m_clockIcon->Init(); }

	//フェードイン
	m_fadeIn = new C_FadeIn();
	if (m_fadeIn) { m_fadeIn->Init(); }

	//フェードアウト
	m_fadeOut = new C_FadeOut();
	if (m_fadeOut) { m_fadeOut->Init(); }

	TotalScoreInit();
	WindowInit();
}

void C_ResultScene::TotalTimerDraw()
{
	// 1. 分・秒・ミリ秒の計算、文字列作成（ここは変更なし）
	int totalSeconds = m_resultFrame / 60;
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	int mSeconds = ((m_resultFrame % 60) * 100) / 60;

	char buf[16];
	if (minutes > 0) {
		sprintf_s(buf, "%02d.%02d.%02d", minutes, seconds, mSeconds);
	}
	else {
		sprintf_s(buf, "%02d.%02d", seconds, mSeconds);
	}
	std::string timeStr = buf;

	// --- 描画設定 ---
	int digitWidth = 16;
	int digitHeight = 32;
	int spacing = 2;

	// 文字列全体の幅を計算（中央揃えにする場合）
	float totalWidth = (float)timeStr.size() * (digitWidth + spacing);

	for (int i = 0; i < (int)timeStr.size(); i++)
	{
		int num = 0;
		if (timeStr[i] >= '0' && timeStr[i] <= '9') {
			num = timeStr[i] - '0';
		}
		else if (timeStr[i] == '.') {
			num = 12;
		}
		else { continue; }

		// --- ここから行列計算を追加 ---

		// ① 各文字を横に並べるための移動量を計算
		float offsetX = (i * (digitWidth + spacing)) - (totalWidth / 2.0f);

		// ② 各文字ごとのオフセット行列を作成
		Math::Matrix offsetMat = Math::Matrix::CreateTranslation(offsetX, 0, 0);

		// ③ Updateで計算済みの m_mat (Scale * Trans) と掛け合わせる
		Math::Matrix finalMat = offsetMat * m_mat;

		// シェーダーに渡す
		SHADER.m_spriteShader.SetMatrix(finalMat);

		// 描画実行
		Math::Rectangle rect = { num * digitWidth, 0, digitWidth, digitHeight };
		SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rect);
	}
}

void C_ResultScene::TotalScoreDraw()
{
	char buf[16];
	sprintf_s(buf, "%08d", m_displayScore);
	std::string scoreStr = buf;

	int digitWidth = 16;
	int spacing = 5;
	float totalWidth = (float)scoreStr.size() * (digitWidth + spacing);

	// --- 演出用の色設定 ---
	// デフォルトは白。if文の中でコンストラクタを使って色を上書きする
	Math::Color color = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (m_step == ResultStep::AddBonus) 
	{
		// 加算中：不透明な黄色
		color = { 1.0f, 1.0f, 0.0f, 1.0f };
	}
	else if (m_step == ResultStep::Finish) 
	{
		// 加算終了後：青成分を増やしてじわ～っと白に戻す
		color = { 1.0f, 1.0f, 1.0f - m_colorLerp, 1.0f };
	}

	for (int i = 0; i < (int)scoreStr.size(); i++) 
	{
		int num = scoreStr[i] - '0';
		float offsetX = (i * (digitWidth + spacing)) - (totalWidth / 2.0f);
		Math::Matrix offsetMat = Math::Matrix::CreateTranslation(offsetX, 0, 0);
		Math::Matrix finalMat = offsetMat * m_scoreMat;

		SHADER.m_spriteShader.SetMatrix(finalMat);

		Math::Rectangle rect = { num * digitWidth, 0, digitWidth, 32 };

		// 設定した color を使って描画
		SHADER.m_spriteShader.DrawTex(&m_scoreTex, 0, 0, &rect, &color);
	}

	// --- ボーナス値（+10000）の描画 ---
	// AddBonus中、またはFinish中でまだ色が戻りきっていない（m_colorLerp > 0）間だけ表示
	if (m_step == ResultStep::AddBonus || (m_step == ResultStep::Finish && m_colorLerp > 0.0f))
	{
		char bonusBuf[16];
		sprintf_s(bonusBuf, "+%d", m_bonus);
		std::string bonusStr = bonusBuf;

		int bWidth = 16;
		float bScale = 1.0f;
		int bSpacing = 2;

		float startX = m_scorePos.x + 100.0f;
		float startY = m_scorePos.y - 40.0f;

		// ボーナスの色設定
		Math::Color bColor = { 1.0f, 1.0f, 0.0f, 1.0f }; // 基本は黄色

		if (m_step == ResultStep::Finish) {
			// 終了後はアルファ値を m_colorLerp に同期させてじわ～っと消す
			bColor = { 1.0f, 1.0f, 0.0f, m_colorLerp };
		}

		for (int i = 0; i < (int)bonusStr.size(); i++) {
			int num = 0;
			if (bonusStr[i] == '+') num = 10; // テクスチャの並びに合わせて調整
			else if (bonusStr[i] >= '0' && bonusStr[i] <= '9') num = bonusStr[i] - '0';
			else continue;

			Math::Matrix bMat = Math::Matrix::CreateScale(bScale, bScale, 1.0f) * Math::Matrix::CreateTranslation(startX + i * (bWidth + bSpacing), startY, 0);

			SHADER.m_spriteShader.SetMatrix(bMat);

			Math::Rectangle rect = { num * bWidth, 0, bWidth, 32 };
			SHADER.m_spriteShader.DrawTex(&m_scoreTex, 0, 0, &rect, &bColor);
		}
	}
}
void C_ResultScene::TotalScoreUpdate()
{
	// ボーナスの計算（Initでも良いですが、確定値として保持）
	m_bonus = 10000 - (m_totalHit * 1000);
	if (m_bonus < 0) m_bonus = 0;

	// 現在の目標スコアをステップごとに設定
	int targetScore = m_clearScore; // 基本は敵撃破スコア
	if (m_step == ResultStep::AddBonus || m_step == ResultStep::Finish) 
	{
		targetScore = m_clearScore + m_bonus; // ボーナス合算後の値
	}

	// --- スコアのカウントアップ処理 ---
	if (m_displayScore < targetScore) 
	{
		int diff = targetScore - m_displayScore;
		int addValue = diff / 20;
		if (addValue < 1) addValue = 1;
		m_displayScore += addValue;
	}
	// 目標に到達した後のステップ遷移
	else if (m_displayScore >= targetScore) 
	{
		if (m_step == ResultStep::BaseScore) 
		{
			m_step = ResultStep::Wait;
			m_waitTimer = 60; // 1秒くらい待つ
		}
		else if (m_step == ResultStep::AddBonus) 
		{
			m_step = ResultStep::Finish;
		}
	}

	// ウェイト処理
	if (m_step == ResultStep::Wait) {
		m_waitTimer--;
		if (m_waitTimer <= 0) {
			m_step = ResultStep::AddBonus;
			// ここで「シャキーン！」と音を鳴らすと最高です
		}
	}

	// 行列更新（今のままでOK！）
	m_scoreTrans = Math::Matrix::CreateTranslation(m_scorePos.x, m_scorePos.y, 0);
	m_scoreScale = Math::Matrix::CreateScale(m_scoreSize.x, m_scoreSize.y, 0);
	m_scoreMat = m_scoreScale * m_scoreTrans;
}

void C_ResultScene::TotalScoreInit()
{
	m_scorePos = { 0,0 };
	m_scoreSize = { 2.0f,2.0f };
	m_scoreTex.Load("Texture/Score/Suuji.png");
}

void C_ResultScene::WindowDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_windowMat);
	SHADER.m_spriteShader.DrawTex(&m_windowTex, Math::Rectangle(0, 0, 940, 1080), 1.0f);
}

void C_ResultScene::WindowUpdate()
{
	m_windowTrans = Math::Matrix::CreateTranslation(m_windowPos.x, m_windowPos.y, 0);
	m_windowScale = Math::Matrix::CreateScale(m_windowSize.x, m_windowSize.y, 0);
	m_windowMat = m_windowScale * m_windowTrans;
}

void C_ResultScene::WindowInit()
{
	m_windowPos = { 0,0 };
	m_windowSize = { 1.4f,0.73f };
	m_windowTex.Load("Texture/Window/Window.png");
}

void C_ResultScene::Release()
{
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
}
