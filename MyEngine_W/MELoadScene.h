#pragma once
#include "../MyEngine_Source/CommonInclude.h"
#include "../MyEngine_Source/MESceneManager.h"
#include "MEPlayScene.h"
#include "MEEndScene.h"
#include "MEScoreScene.h"
#include "METitleScene.h"
#include "MEGameOverScene.h"


namespace ME
{
	void LoadScenes()
	{
		
		
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<GameOverScene>(L"GameOverScene");
	//SceneManager::CreateScene<EndScene>(L"EndScene");
		//SceneManager::CreateScene<ScoreScene>(L"ScoreScene");
		
		
		//SceneManager::LoadScene(L"PlayScene");

		SceneManager::LoadScene(L"TitleScene");
		//SceneManager::LoadScene(L"GameOverScene");
		
		//SceneManager::LoadScene(L"ScoreScene");

		//SceneManager::LoadScene(L"EndScene");


	}
}
