#pragma once
#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "../MyEngine_Source/MECollider.h"

namespace ME
{


	class PlayerScript :public Script
	{
	public:
		enum class eState
		{	
			Standing,
			Attack,
			Jump,
			Run,
			Walk,
			Fall,
			GetDown,
			Move,
			Die
		};

		enum class ePrevDirection
		{
			Left,
			Right
			
		};

		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;
		
		void MakeBullet();

		ePrevDirection GetPrevDirection() { return mPrevDirection; }

	private:

		void Standing();
		void Move();
		void Jump();
		void Run();
		void Attack();
		void Die();

		void PlayStandingAnimByPrevDirection();
		void PlayBulletByPrveDirection(Animator* animator);

	private:
		bool isJump;
		float jumpSeconds;
		float mHp;

		eState mState;
		ePrevDirection mPrevDirection;

		class Animator* mAnimator;
	};
}

