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

	void SetLevel1Flg(bool level1Flg) { m_level1Flg = level1Flg; }
	bool GetLevel1Flg() { return m_level1Flg; }


	void SetLevel2Flg(bool level2Flg) { m_level2Flg = level2Flg; }
	bool GetLevel2Flg() { return m_level2Flg; }

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

	float m_alpha1; // Level 1 ‚Ì“§–¾“x 
	float m_alpha2; // Level 2 ‚Ì“§–¾“x 

	float m_fadeSpeed;

	bool m_level1Flg;
	bool m_level2Flg;

};
