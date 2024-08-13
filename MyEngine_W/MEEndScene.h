#pragma once
#include "../MyEngine_Source/MEScenes.h"


namespace ME
{
	class EndScene: public Scene
	{
	public:
		EndScene();
		~EndScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC mHdc) override;



	private:

	};

}
