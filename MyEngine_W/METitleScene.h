#pragma once
#include "../MyEngine_Source/MEScenes.h"

namespace ME
{
	class TitleScene:public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC mHdc) override;
	private:

	};
}

