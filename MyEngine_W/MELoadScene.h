#pragma once
#include "../MyEngine_Source/CommonInclude.h"
#include "../MyEngine_Source/MESceneManager.h"
#include "MEPlayScene.h"
#include "MEEndScene.h"
#include "MEScoreScene.h"
#include "METitleScene.h"


namespace ME
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
	//	SceneManager::CreateScene<EndScene>(L"EndScene");
		//SceneManager::CreateScene<ScoreScene>(L"ScoreScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		
		SceneManager::LoadScreen(L"PlayScene");
		SceneManager::LoadScreen(L"TitleScene");

		
		//SceneManager::LoadScreen(L"ScoreScene");

		//SceneManager::LoadScreen(L"EndScene");


	}
}
