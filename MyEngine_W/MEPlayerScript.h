#pragma once
#include "../MyEngine_Source/MEScript.h"

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
			Move
		};

		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:

		void Standing();
		void Move();
		void Attack();

	private:
		bool isJump;
		int jumpSeconds;

		eState mState;
		eState mPrevState;

		class Animator* mAnimator;
	};
}

