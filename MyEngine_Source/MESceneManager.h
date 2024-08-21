#pragma once
#include "CommonInclude.h"
#include "MEScenes.h"

namespace ME
{
	class SceneManager
	{
	public:
		template<typename T>
		
		static Scene* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mActiveScene = scene;	
			scene->Initialize();

			mScene.insert({ name, scene });

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		
		static Scene* GetActiveScene() { return mActiveScene; }



		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC mHdc);
		static void Destroy();

		static void Release();

	private:
		
		static std::map<std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
	};

}

