#pragma once
#include "../MyEngine_Source/MEScenes.h"
#include "../MyEngine_Source/MESceneManager.h"


namespace ME
{
	class ToolScene :public Scene
	{
	public:

		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC mHdc)override;
		void Destroy()override;

		void OnEnter()override;
		void OnExit()override;

	private:

	};

}

