#include "METurtleScript.h"
#include "../MyEngine_Source/MEInput.h"
#include "../MyEngine_Source/MEGameObject.h"
#include "../MyEngine_Source/METime.h"


namespace ME
{
	TurtleScript::TurtleScript()
	{
	}
	TurtleScript::~TurtleScript()
	{
	}
	void TurtleScript::Initialize()
	{
	
		
	}
	void TurtleScript::Update()
	{

		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}


		switch (mState)
		{
		case ME::TurtleScript::eState::Idle:
			Idle();
			break;
		case ME::TurtleScript::eState::Walk:
			Move();
			break;
		default:
			break;
		}
	}

	void TurtleScript::Idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.5f)
		{
			mState = eState::Walk;
			int direction = rand() % 3;
			mDirection = (eDirection)direction;
			PlayAnimationByDirection(mDirection);

			mTime = 0;
		}
	}

	void TurtleScript::Move()
	{
		mTime += Time::DeltaTime();

		if (mTime > 2.0f)
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Translate(tr);

	}

	void TurtleScript::Translate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();

		switch (mDirection)
		{
		case ME::TurtleScript::eDirection::Left:
			pos.x -= 10 * Time::DeltaTime();
			break;
		case ME::TurtleScript::eDirection::Right:
			pos.x += 10 * Time::DeltaTime();
			break;
		case ME::TurtleScript::eDirection::End:
			break;
		default:
			break;
		}

		tr->SetPosition(pos);
	}

	void TurtleScript::PlayAnimationByDirection(eDirection direction)
	{
		switch (direction)
		{
		case ME::TurtleScript::eDirection::Left:
			mAnimator->PlayAnimation(L"TurtleLeftWalk", true);
			break;
		case ME::TurtleScript::eDirection::Right:
			mAnimator->PlayAnimation(L"TurtleRightWalk", true);
			break;
		case ME::TurtleScript::eDirection::End:
			mAnimator->PlayAnimation(L"idle", false);
			break;
		default:
			break;
		}
	}

	void TurtleScript::LateUpdate()
	{
	}
	void TurtleScript::Render(HDC hdc)
	{
	}
}