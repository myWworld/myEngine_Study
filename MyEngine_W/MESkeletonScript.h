#pragma once

#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "METransform.h"
#include "../MyEngine_Source/MECollider.h"

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

		SkeletonScript();
		~SkeletonScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void OnCollisionEnter( Collider* other) override;
		void OnCollisionStay( Collider* other) override;
		void OnCollisionExit( Collider* other) override;

		eDirection GetDirection() { return mDirection; }

		float GetHp() { return mHp; }

		void Respawn();

	private:
		
		void Idle();
		void Attack();
		void Shout();
		void Move();
		void Translate(Transform *tr);
		void Die();
		void Hurt();
		
		void PlayAnimationByStateAndDirection();

	private:

		Animator* mAnimator;

		float mTime;

		float mRespawnTime;
		float mHp;
		bool mbIsDead;
		bool mbISRespawn;

		eState mSkeletonState;
		eDirection mDirection;
	};


}