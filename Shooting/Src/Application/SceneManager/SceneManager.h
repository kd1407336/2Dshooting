#pragma once
#include "Application/State/State.h"
#include "../GameScene/GameScene.h"
#include "Application/Result/Result.h"
#include "Application/TitleScene/TitleScene.h"

class C_SceneManager
{
public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}
	
	void ChangeState(C_State* newState)
	{
		delete currentState;
		currentState = newState;
		currentState->Init();
	}
	
	void Update()
	{
		currentState->Update();
	}

	void Draw()
	{
		currentState->Draw();
	}


private:

	C_SceneManager() {}
	C_State* currentState = nullptr;
};

#define SCENEMANAGER C_SceneManager::GetInstance()