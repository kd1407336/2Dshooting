#pragma once

class C_Level
{
public:

	C_Level(){}
	~C_Level(){}

	void Level1Draw();
	void Level1Update();
	void Level1Init();

	void Level2Draw();
	void Level2Update();
	void Level2Init();

	void Level3Draw();
	void Level3Update();
	void Level3Init();

	void LevelMaxDraw();
	void LevelMaxUpdate();
	void LevelMaxInit();

	void SetLevel1Flg(bool level1Flg) { m_level1Flg = level1Flg; }
	bool GetLevel1Flg() { return m_level1Flg; }


	void SetLevel2Flg(bool level2Flg) { m_level2Flg = level2Flg; }
	bool GetLevel2Flg() { return m_level2Flg; }

	void SetLevel3Flg(bool a_flg) { m_level3Flg = a_flg; }
	bool GetLevel3Flg() { return m_level3Flg; }

	void SetLevelMaxFlg(bool a_flg) { m_levelMaxFlg = a_flg; }
	bool GetLevelMaxFlg() const { return m_levelMaxFlg; }

private:

	Math::Vector2 m_pos;
	Math::Vector2 m_size;
	Math::Matrix m_mat;
	Math::Matrix m_scale;
	Math::Matrix m_trans;
	KdTexture m_tex;

	Math::Vector2 m_levelPos;
	Math::Vector2 m_levelSize;
	Math::Matrix m_levelMat;
	Math::Matrix m_levelScale;
	Math::Matrix m_levelTrans;
	KdTexture m_levelTex;

	
	Math::Vector2 m_level3Pos;
	Math::Vector2 m_level3Size;
	Math::Matrix m_level3Mat;
	Math::Matrix m_level3Trans;
	Math::Matrix m_level3Scale;
	KdTexture m_level3Tex;
	float m_alpha3;
	bool m_level3Flg;

	Math::Vector2 m_levelMaxPos;
	Math::Vector2 m_levelMaxSize;
	Math::Matrix m_levelMaxMat;
	Math::Matrix m_levelMaxTrans;
	Math::Matrix m_levelMaxScale;
	KdTexture m_levelMaxTex;
	float m_alphaMax;
	bool m_levelMaxFlg;




	float m_alpha1; // Level 1 ‚Ì“§–¾“x 
	float m_alpha2; // Level 2 ‚Ì“§–¾“x 

	float m_fadeSpeed;

	float m_alpha2Speed;
	float m_alpha3Speed;

	bool m_level1Flg;
	bool m_level2Flg;

};
