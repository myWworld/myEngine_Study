#pragma once
#include "../MyEngine_Source/CommonInclude.h"
#include "../MyEngine_Source/MESceneManager.h"
#include "MEPlayScene.h"
#include "MEEndScene.h"
#include "MEScoreScene.h"
#include "METitleScene.h"
#include "MEGameOverScene.h"
#include "METoolScene.h"

namespace ME
{
	void LoadScenes()
	{
		
		
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<GameOverScene>(L"GameOverScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

	//SceneManager::CreateScene<EndScene>(L"EndScene");
		//SceneManager::CreateScene<ScoreScene>(L"ScoreScene");
		
		
		SceneManager::LoadScene(L"ToolScene");

		//SceneManager::LoadScene(L"TitleScene");
	

	}
}
