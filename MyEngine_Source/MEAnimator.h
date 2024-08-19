#pragma once

#include "MEComponent.h"
#include "MEAnimation.h"
#

namespace ME
{


	class Animator:public Component
	{
	public:
		
		Animator();
		~Animator();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, float duration
			, UINT spriteLength
			, UINT spriteLength2 = 0);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

	private:

		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		bool mbLoop;

	};


}