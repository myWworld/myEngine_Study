#pragma once
#include "../MyEngine_Source/MEScenes.h"


namespace ME
{
	class ScoreScene: public Scene
	{
	public:
			
		ScoreScene();
		~ScoreScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC mHdc) override;

	private:

	};

}
