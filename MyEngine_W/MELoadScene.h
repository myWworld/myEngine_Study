#pragma once
#include "../MyEngine_Source/MESceneManager.h"
#include "MEPlayScene.h"

namespace ME
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::LoadScreen(L"PlayScene");


	}
}
