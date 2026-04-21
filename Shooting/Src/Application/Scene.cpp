#include "main.h"
#include "Scene.h"
#include "SceneManager/SceneManager.h"

void Scene::Draw2D()
{
	SCENEMANAGER.Draw();
}

void Scene::Update()
{
	SCENEMANAGER.Update();

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}

	if (GetAsyncKeyState('G') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_GameScene());
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_Result());
	}

}

void Scene::Init()
{
	SCENEMANAGER.ChangeState(new C_TitleScene());

}

void Scene::Release()
{
	
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
