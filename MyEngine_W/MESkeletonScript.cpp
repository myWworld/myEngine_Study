#include "MESkeletonScript.h"
#include "../MyEngine_Source/MEInput.h"
#include "../MyEngine_Source/MEGameObject.h"
#include "../MyEngine_Source/METime.h"

namespace ME
{
	void SkeletonScript::Initialize()
	{
	}
	void SkeletonScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case ME::SkeletonScript::eState::Idle:
			Idle();
			break;
		case ME::SkeletonScript::eState::Shout:
			Shout();
			break;
		case ME::SkeletonScript::eState::Attack:
			Attack();
			break;
		case ME::SkeletonScript::eState::Walk:
			Move();
			break;
		case ME::SkeletonScript::eState::Hurt:
			Move();
			break;
		case ME::SkeletonScript::eState::Die:
			Move();
			break;
		default:
			break;
		}
	}
	void SkeletonScript::Idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			int state = rand() % 4;
			int direction = rand() % 2;

			mDirection = (eDirection)direction;
			mState = (eState)state;

			PlayAnimationByStateAndDirection();

			mTime = 0;
		}
	}


	void SkeletonScript::Shout()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Idle;
		}
	}
	void SkeletonScript::Attack()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Idle;
		}
	}
	void SkeletonScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		mTime += Time::DeltaTime();

	
		Translate(tr);

		if (mTime > 2.5f)
		{
			mState = eState::Idle;
			mTime = 0;
		}
	}


	void SkeletonScript::Translate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();

		switch (mDirection)
		{
		case ME::SkeletonScript::eDirection::Right:
			pos.x += 20 * Time::DeltaTime();
			break;
		case ME::SkeletonScript::eDirection::Left:
			pos.x -= 20 * Time::DeltaTime();
			break;
		default:
			break;
		}

		tr->SetPosition(pos);

	}
		

	void SkeletonScript::PlayAnimationByStateAndDirection()
	{
		if (mDirection == eDirection::Right)
		{
			switch (mState)
			{
			case ME::SkeletonScript::eState::Idle:
				mAnimator->PlayAnimation(L"SkeletonIdleR");
				break;
			case ME::SkeletonScript::eState::Shout:
				mAnimator->PlayAnimation(L"SkeletonShoutR",false);
				break;
			case ME::SkeletonScript::eState::Attack:
				mAnimator->PlayAnimation(L"SkeletonAttackR", false);
				break;
			case ME::SkeletonScript::eState::Walk:
				mAnimator->PlayAnimation(L"SkeletonWalkR");
				break;
			default:
				break;
			}
		}
		else if (mDirection == eDirection::Left)
		{
			switch (mState)
			{
			case ME::SkeletonScript::eState::Idle:
				mAnimator->PlayAnimation(L"SkeletonIdleL");
				break;
			case ME::SkeletonScript::eState::Shout:
				mAnimator->PlayAnimation(L"SkeletonShoutL", false);
				break;
			case ME::SkeletonScript::eState::Attack:
				mAnimator->PlayAnimation(L"SkeletonAttackL", false);
				break;
			case ME::SkeletonScript::eState::Walk:
				mAnimator->PlayAnimation(L"SkeletonWalkL");
				break;
			default:
				break;
			}
		}
	}

	void SkeletonScript::LateUpdate()
	{
	}
	void SkeletonScript::Render(HDC hdc)
	{
	}
}