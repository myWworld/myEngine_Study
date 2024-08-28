#pragma once
#include "../MyEngine_Source/METexture.h"
#include "../MyEngine_Source/MEScenes.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "../MyEngine_Source/MECamera.h"

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

	 void OnEnter() override;
	 void OnExit() override;

	private:

		void CreatePlayerAnimation(Animator *animator, graphics::Texture* Rtexture, graphics::Texture* Ltexture);
		void CreateMushRoomAnimation(Animator* animator, graphics::Texture* Rtexture, graphics::Texture* Ltexture);
		void CreateSkeletonAnimation(Animator* animator, graphics::Texture* Rtexture, graphics::Texture* Ltexture);

		void playerInitialize();

	private:

		class GameObject* mPlayer;
		class Camera* mCameraComp;
	};
}
