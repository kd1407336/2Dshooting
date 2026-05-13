#include "Result.h"
#include "../Fade/FadeIn.h"
#include "../Fade/FadeOut.h"
#include "Application/ClockIcon/ClockIcon.h"
#include "Application/Result/ResultLogo.h" 
#include "Application/SceneManager/SceneManager.h"

C_ResultScene::C_ResultScene(int clearFrame,int clearScore,int hitCount, bool isClear)
	  : m_resultFrame(clearFrame),
		m_clearScore(clearScore),
		m_totalHit(hitCount),
		m_isClear(isClear)
{


	// ロゴクラスの生成
	m_resultLogo = new C_ResultLogo();

	// ロゴの初期化（ここで true/false を渡すことで内部の変数が切り替わる）
	m_resultLogo->Init(m_isClear);
}

void C_ResultScene::Draw()
{
	WindowDraw();
	TotalTimerDraw();
	TotalScoreDraw();
	ScoreDraw();

	if (m_clockIcon) { m_clockIcon->Draw(); }
	if (m_resultLogo) { m_resultLogo->Draw(); }

	if(m_fadeIn){m_fadeIn->Draw();}
	if(m_fadeOut){m_fadeOut->Draw();}
	
}

void C_ResultScene::Update()
{
	if (m_clockIcon) { m_clockIcon->Update(); m_clockIcon->SetAliveFlg(true); }
	if (m_fadeIn) { m_fadeIn->Update(); }
	if (m_fadeOut) { m_fadeOut->Update(); }
	// ロゴの更新（フェードや行列計算が行われる）
	if (m_resultLogo){m_resultLogo->Update();}

	ScoreUpdate();
	TotalScoreUpdate();
	TotalTimerUpdate();
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
	m_pos = { 10,60 };
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
	ScoreInit();
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

	// 文字列全体の幅を計算
	float totalWidth = (float)timeStr.size() * (digitWidth + spacing);

	// ★追加：1分を超えた場合（文字数が増えた場合）の離し具合を調整
	float baseOffsetX = 0.0f;
	if (minutes > 0) {
		baseOffsetX = 30.0f; // ここの数値を大きくすると、アイコンからより離れます
	}

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

		// ① 各文字の並び順に、baseOffsetX を加算して全体をずらす
		float offsetX = (i * (digitWidth + spacing)) - (totalWidth / 2.0f) + baseOffsetX;

		// ② オフセット行列を作成
		Math::Matrix offsetMat = Math::Matrix::CreateTranslation(offsetX, 0, 0);

		// ③ 合成
		Math::Matrix finalMat = offsetMat * m_mat;

		SHADER.m_spriteShader.SetMatrix(finalMat);

		Math::Rectangle rect = { num * digitWidth, 0, digitWidth, digitHeight };
		SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rect);
	}
}

void C_ResultScene::TotalTimerUpdate()
{
	// フレーム数で定義（60fps想定）
	const int SEC_30 = 30 * 60; // 1800フレーム
	const int SEC_60 = 60 * 60; // 3600フレーム
	const int SEC_90 = 90 * 60; // 5400フレーム

	if (m_resultFrame <= SEC_30)
	{
		// 0秒 ～ 30.00秒まで
		m_timerBonus = 10000;
	}
	else if (m_resultFrame <= SEC_60)
	{
		// 30.01秒 ～ 60.00秒まで（31秒以上を含む区間）
		m_timerBonus = 8000;
	}
	else if (m_resultFrame <= SEC_90)
	{
		// 60.01秒 ～ 90.00秒まで
		m_timerBonus = 5000;
	}
	else
	{
		// それ以上
		m_timerBonus = 0;
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

	// メインスコアの色（加算中は黄色）
	Math::Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (m_step == ResultStep::Finish && m_colorLerp > 0.0f) {
		color = { 1.0f, 1.0f, 1.0f - m_colorLerp, 1.0f }; // 黄色寄り
	}

	// メインスコア描画
	for (int i = 0; i < (int)scoreStr.size(); i++) {
		int num = scoreStr[i] - '0';
		float offsetX = (i * (digitWidth + spacing)) - (totalWidth / 2.0f);
		Math::Matrix finalMat = Math::Matrix::CreateTranslation(offsetX, 0, 0) * m_scoreMat;
		SHADER.m_spriteShader.SetMatrix(finalMat);
		Math::Rectangle rect = { num * digitWidth, 0, digitWidth, 32 };
		SHADER.m_spriteShader.DrawTex(&m_scoreTex, 0, 0, &rect, &color);
	}

	// 右側ボーナスの表示判定
	// ヒットボーナス表示開始 ～ メイン加算が終わるまで
	bool isVisible = (m_step >= ResultStep::AddHitBonus && m_step <= ResultStep::Finish);

	if (isVisible) {
		char bonusBuf[16];
		sprintf_s(bonusBuf, "+%d", m_currentBonusDisplay);
		std::string bonusStr = bonusBuf;

		float startX = m_scorePos.x + 160.0f;
		float startY = m_scorePos.y - 30.0f;
		Math::Color bColor = { 1.0f, 1.0f, 0.0f, 1.0f };

		// メイン加算開始後は徐々に消えていく演出
		if (m_step == ResultStep::Finish) {
			bColor.A(m_colorLerp);
		}

		for (int i = 0; i < (int)bonusStr.size(); i++) {
			int num = (bonusStr[i] == '+') ? 10 : bonusStr[i] - '0';
			Math::Matrix bMat = Math::Matrix::CreateTranslation(startX + i * 18, startY, 0);
			SHADER.m_spriteShader.SetMatrix(bMat);
			Math::Rectangle rect = { num * 16, 0, 16, 32 };
			SHADER.m_spriteShader.DrawTex(&m_scoreTex, 0, 0, &rect, &bColor);
		}
	}
}

void C_ResultScene::TotalScoreUpdate()
{
	// --- 1. ボーナス計算の同期 ---
	int hitBonusMax = 10000 - (m_totalHit * 1000);
	if (hitBonusMax < 0) hitBonusMax = 0;

	// ★ここを修正：TotalTimerUpdateで計算された m_timerBonus を直接使う
	int timeBonusMax = m_timerBonus;

	// 最終合計スコア（ベーススコア + 被弾ボーナス + タイムボーナス）
	int finalTotal = m_clearScore + hitBonusMax + timeBonusMax;

	// --- 2. 目標値の設定 ---
	int bonusTarget = 0;
	if (m_step == ResultStep::AddHitBonus)
	{
		bonusTarget = hitBonusMax;
	}
	else if (m_step >= ResultStep::WaitTime)
	{
		// 被弾ボーナスとタイムボーナスの合算値を目標にする
		bonusTarget = hitBonusMax + timeBonusMax;
	}

	// --- 3. 徐々に増やす処理 ---
	if ((m_step == ResultStep::AddHitBonus || m_step >= ResultStep::AddTimeBonus) && m_currentBonusDisplay < bonusTarget) {
		int diff = bonusTarget - m_currentBonusDisplay;
		int addValue = diff / 15;
		if (addValue < 1) addValue = 1;
		m_currentBonusDisplay += addValue;
	}

	// --- 4. ステップ遷移ロジック ---
	switch (m_step)
	{
	case ResultStep::BaseScore:
		m_displayScore = m_clearScore;
		m_currentBonusDisplay = 0;
		m_waitTimer = 60;
		m_step = ResultStep::WaitHit;
		break;

	case ResultStep::WaitHit:
		if (--m_waitTimer <= 0) m_step = ResultStep::AddHitBonus;
		break;

	case ResultStep::AddHitBonus:
		if (m_currentBonusDisplay >= hitBonusMax)
		{
			m_waitTimer = 45;
			m_step = ResultStep::WaitTime;
		}
		break;

	case ResultStep::WaitTime:
		if (--m_waitTimer <= 0) m_step = ResultStep::AddTimeBonus;
		break;

	case ResultStep::AddTimeBonus:
		// timeBonusMax(m_timerBonus) を含めた合計まで増やす
		if (m_currentBonusDisplay >= (hitBonusMax + timeBonusMax))
		{
			m_waitTimer = 60;
			m_step = ResultStep::Finish;
		}
		break;

	case ResultStep::Finish:
		if (m_displayScore < finalTotal)
		{
			int diff = finalTotal - m_displayScore;
			int addValue = diff / 10;
			if (addValue < 1) addValue = 1;
			m_displayScore += addValue;
			m_colorLerp = 1.0f;
		}
		else
		{
			m_colorLerp -= 0.05f;
			if (m_colorLerp < 0) m_colorLerp = 0;
		}
		break;
	}

	// 行列更新
	m_scoreTrans = Math::Matrix::CreateTranslation(m_scorePos.x, m_scorePos.y, 0);
	m_scoreScale = Math::Matrix::CreateScale(m_scoreSize.x, m_scoreSize.y, 1.0f);
	m_scoreMat = m_scoreScale * m_scoreTrans;
}
void C_ResultScene::TotalScoreInit()
{
	m_scorePos = { 95,-100 };
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

void C_ResultScene::ScoreDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_scoreMojiMat);
	// 描画
	SHADER.m_spriteShader.DrawTex(&m_scoreMojiTex, Math::Rectangle(0, 0, 140, 50), 1.0f);
}

void C_ResultScene::ScoreUpdate()
{
	m_scoreMojiTrans = Math::Matrix::CreateTranslation(m_scoreMojiPos.x, m_scoreMojiPos.y, 0);
	m_scoreMojiScale = Math::Matrix::CreateScale(m_scoreMojiSize.x, m_scoreMojiSize.y, 0);
	m_scoreMojiMat = m_scoreMojiScale * m_scoreMojiTrans;
}

void C_ResultScene::ScoreInit()
{
	m_scoreMojiPos = { -190,-100 };
	m_scoreMojiSize = { 1.5f,1.5f };
	m_scoreMojiTex.Load("Texture/Score/Score.png");
}


void C_ResultScene::Release()
{
	if (m_fadeIn) { delete m_fadeIn; m_fadeIn = nullptr; }
	if (m_fadeOut) { delete m_fadeOut; m_fadeOut = nullptr; }
	// メモリ解放
	if (m_resultLogo){delete m_resultLogo;m_resultLogo = nullptr;}
}
