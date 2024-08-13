#pragma once
#include "../MyEngine_Source/MEScenes.h"

namespace ME
{

	class PlayScene : public Scene
	{
	public:
	
		PlayScene(); 
		~PlayScene();
		

	 void Initialize() override;
	 void Update() override;
	 void LateUpdate() override;
	 void Render(HDC mHdc) override;

	private:

	};
}
