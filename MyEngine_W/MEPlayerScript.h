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

		static void PlusScore() { PlayerScript::mScore += 10.0f; }
		static float GetHp() { return mHp; }
		static void ReSetHp(float hp) { mHp = hp; }
		static void ReSetScore(int score) { mScore = score; }

		void SetEffect(GameObject* effect) { mEffect = effect; }
		static bool IsStar() { return mbIsStar; }

	private:

		void Standing();
		void Move();
		void Jump();
		void Run();
		void Attack();
		void Die();

		void PrintScore(HDC hdc);

		
		void PlayStandingAnimByPrevDirection();
		void PlayBulletByPrveDirection(Animator* animator);
		void PlayAuraAnimation();
		GameObject* CreateAura();



	private:
		bool isJump;
		float jumpSeconds;
		static float mHp;
		static int mScore;

		static bool mbIsStar;
		float mStarTime;
		
		eState mState;
		ePrevDirection mPrevDirection;

		class Animator* mAnimator;
		class GameObject* mEffect;
	};
}

