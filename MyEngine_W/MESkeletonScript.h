#pragma once

#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "METransform.h"


namespace ME
{


	class SkeletonScript:public Script
	{
	public:

		enum class eState
		{	
			Idle,
			Shout,
			Attack,
			Walk,
			Hurt,
			Die,

		};

		enum class eDirection
		{
			Right,
			Left,
		};

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:
		
		void Idle();
		void Attack();
		void Shout();
		void Move();
		void Translate(Transform *tr);
		
		void PlayAnimationByStateAndDirection();

	private:

		Animator* mAnimator;

		float mTime;

		eState mState;
		eDirection mDirection;
	};


}