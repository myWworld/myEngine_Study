#pragma once
#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "METransform.h"
#include "../MyEngine_Source/MECollider.h"

namespace ME
{


	class MushRoomScript :public Script
	{
	public:

		enum class eState
		{
			Idle,
			Walk,
			Die,
			Hurt,

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

		void OnCollisionEnter( Collider* other) override;
		void OnCollisionStay( Collider* other) override;
		void OnCollisionExit( Collider* other) override;

		eDirection GetDirection() { return mDirection; }

		void Respawn();

		float GetHp() { return mHp; }

		void Hurt();


	private:

		void Idle();
		void Move();
		void Die();
		void PlayAnimationByDirection(eDirection direction);
		void Translate(Transform* tr);

	private:

		eState mState;
		eDirection mDirection;

		float mTime;
		float mSpeed;

		class Animator* mAnimator;

		float mRespawnTime;
		float mHp;
		bool mbIsDead;
		bool mbIsRespawn;
	};

}

