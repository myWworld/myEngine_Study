#pragma once
#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "METransform.h"

namespace ME
{


	class MushRoomScript :public Script
	{
	public:

		enum class eState
		{
			Idle,
			Walk,

		};

		enum class eDirection
		{
			Left,
			Right,
			End,
		};

		MushRoomScript();
		~MushRoomScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:

		void Idle();
		void Move();

		void PlayAnimationByDirection(eDirection direction);
		void Translate(Transform* tr);

	private:

		eState mState;
		eDirection mDirection;

		float mTime;

		class Animator* mAnimator;

	};

}

