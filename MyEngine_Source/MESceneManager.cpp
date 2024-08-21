#include "MESceneManager.h"

namespace ME
{

	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		std::map<std::wstring, Scene*> ::iterator iter
			= mScene.find(name);

		if (iter == mScene.end())
		{
			return nullptr;
		}

		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}


	 
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render(HDC mHdc)
	{
		mActiveScene->Render(mHdc);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (auto& iter : mScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}
