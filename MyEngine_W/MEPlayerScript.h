#pragma once
#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEAnimator.h"
#include "../MyEngine_Source/MECollider.h"
#include "../MyEngine_Source/METexture.h"
#include "../MyEngine_Source/MERigidbody.h"

namespace ME
{


	class PlayerScript :public Script
	{
	public:
		enum class eState
		{	
			Standing,
			StandAttack,
			RunningAttack,
			Jump,
			Run,
			Walk,
			Fall,
			GetDown,
			Move,
			Die,
			Clear,
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
		
		void MakeBullet(bool isRunning = false);


		ePrevDirection GetPrevDirection() { return mPrevDirection; }

		static void PlusScore() { PlayerScript::mScore += 10.0f; }
		static float GetHp() { return mHp; }
		static void ReSetHp(float hp) { mHp = hp; }
		static void ReSetScore(int score) { mScore = score; }

		void SetEffect(GameObject* effect) { mEffect = effect; }
		static bool IsStar() { return mbIsStar; }

		void SetPixelTexture(graphics::Texture* texture) { mPixelTexture = texture; }

	private:

		void Standing();
		void Move();
		void Jump();
		void Run();
		void RunningAttack();
		void StandingAttack();
		void Die();
		void StageClear();

		void PrintScore(HDC hdc);
		void RunAttackTime();
		
		void PlayStandingAnimByPrevDirection();
		void PlayBulletByPrveDirection(Animator* animator);
		void PlayJumpAnimationByPrevDirection();

		void HurtByMonster(Rigidbody* rb, float rightOrLeft);
		void PlayAuraAnimation();


		GameObject* CreateAura();



	private:

		bool isJump;
		float jumpSeconds;

		float mAttackTime;
		bool mbIsRunningAttack;
		
		static bool mbIsStar;
		float mStarTime;
		bool mbStillStartTime;

		static float mHp;
		static int mScore;

		bool mbIsOnFlag;
			
		eState mState;
		ePrevDirection mPrevDirection;

		class Animator* mAnimator;
		class GameObject* mEffect;

		graphics::Texture* mPixelTexture;


	};
}

