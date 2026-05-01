#pragma once


class MouseManager
{
public:
	MouseManager(){}
	~MouseManager(){}


	void Update();


	Math::Vector2 GetPos() { return m_pos; }				//マウス座標
	bool LeftClickDown()const { return m_leftClickDown; }		//マウスをクリックの検査用
	bool LeftClickPress()const { return m_leftClickPress; }		//マウスを押すの検査用
	bool LeftClickUp()const { return m_leftClickUp; }			//マウスをクリックしないの検査用
	bool PrevLeft()const { return m_prevLeft; }

	bool RightClickDown()const { return m_rightClickDown; }		//マウスをクリックの検査用
	bool RightClickPress()const { return m_rightClickPress; }		//マウスを押すの検査用
	bool RightClickUp()const { return m_rightClickUp; }			//マウスをクリックしないの検査用
	bool PrevRight()const { return m_prevRight; }


	bool IsInRect(const Math::Rectangle& rect) const;
	bool ClickRect(const Math::Rectangle& rect) const;

private:

	Math::Vector2 m_pos;
	bool m_leftClickDown = false;		//マウスをクリックの検査用
	bool m_leftClickPress = false;		//マウスを押すの検査用
	bool m_leftClickUp = false;			//マウスをクリックしないの検査用
	bool m_prevLeft = false;

	bool m_rightClickDown = false;		//マウスをクリックの検査用
	bool m_rightClickPress = false;		//マウスを押すの検査用
	bool m_rightClickUp = false;			//マウスをクリックしないの検査用
	bool m_prevRight = false;


	static const int ScrWidth = 1280;	//画面の幅さ
	static const int ScrHeight = 720;	//画面の高さ
};

// =============================
// 使い方
// =============================
// #include"MouseManager.h"
// 
// extern Mouse g_mouse;　<----追加が必要、追加しなければ、マウスの位置判定はエラーがある
