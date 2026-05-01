#include "MouseManager.h"
#include"../main.h"

MouseManager g_mouse;

void MouseManager::Update()
{
    //マウス座標を取得
    POINT mousePos;
    GetCursorPos(&mousePos);

    ScreenToClient(APP.m_window.GetWndHandle(), &mousePos);

    //キャラの座標とマウス座標を修正
    mousePos.x -= ScrWidth / 2;
    mousePos.y -= ScrHeight / 2;
    mousePos.y *= -1;


    m_pos = { (float)mousePos.x, (float)mousePos.y };

    //マウス状態検査用
    bool nowLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

    m_leftClickDown = (nowLeft && !m_prevLeft);     //マウスをクリック
    m_leftClickPress = nowLeft;                     //マウスを押す
    m_leftClickUp = (!nowLeft && m_prevLeft);       //マウスのキーを離す

    m_prevLeft = nowLeft;                           //マウス

    bool nowRight = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);

    m_rightClickDown = (nowRight && !m_prevRight);     //マウスをクリック
    m_rightClickPress = nowRight;                     //マウスを押す
    m_rightClickUp = (!nowRight && m_prevRight);       //マウスのキーを離す

    m_prevRight = nowRight;                           //マウス
}



bool MouseManager::IsInRect(const Math::Rectangle& rect) const
{
    return (m_pos.x >= rect.x &&
        m_pos.x <= rect.x + rect.width &&
        m_pos.y >= rect.y &&
        m_pos.y <= rect.y + rect.height);
}

bool MouseManager::ClickRect(const Math::Rectangle& rect) const
{
    return LeftClickDown() && IsInRect(rect);
}
