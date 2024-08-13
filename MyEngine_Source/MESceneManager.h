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
			scene->Initialize();

			mScene.insert({ name, scene });

			return scene;
		}

		static Scene* LoadScreen(const std::wstring& name)
		{
			std::map<std::wstring, Scene*> ::iterator iter
			 = mScene.find(name);
		
			if (iter == mScene.end())
			{
				return nullptr;
			}
			
			mActiveScene = iter->second;

			return iter->second;
		}



		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC mHdc);

	private:
		
		static std::map<std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
	};

}

