#include "MEMushRoomScript.h"
#include "../MyEngine_Source/MEInput.h"
#include "../MyEngine_Source/MEGameObject.h"
#include "../MyEngine_Source/METime.h"


namespace ME
{
	MushRoomScript::MushRoomScript()
		:mSpeed(25.0f)
	{
	}
	MushRoomScript::~MushRoomScript()
	{
	}
	void MushRoomScript::Initialize()
	{
	
		
	}
	void MushRoomScript::Update()
	{

		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}


		switch (mState)
		{
		case ME::MushRoomScript::eState::Idle:
			Idle();
			break;
		case ME::MushRoomScript::eState::Walk:
			Move();
			break;
		default:
			break;
		}
	}

	void MushRoomScript::Idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			mState = eState::Walk;
			int direction = rand() % 3;
			mDirection = (eDirection)direction;
			PlayAnimationByDirection(mDirection);

			mTime = 0;
		}
	}

	void MushRoomScript::Move()
	{
		mTime += Time::DeltaTime();


		if (mDirection == eDirection::End || mTime > 2.0f)
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"IdleL", false);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Translate(tr);

	}

	void MushRoomScript::Translate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();

		switch (mDirection)
		{
		case ME::MushRoomScript::eDirection::Left:
			pos += Vector2::Left * (mSpeed * Time::DeltaTime());
			break;
		case ME::MushRoomScript::eDirection::Right:
			pos += Vector2::Right * (mSpeed * Time::DeltaTime());
			break;
		case ME::MushRoomScript::eDirection::End:
			break;
		default:
			break;
		}

		tr->SetPosition(pos);
	}

	void MushRoomScript::PlayAnimationByDirection(eDirection direction)
	{
		switch (direction)
		{
		case ME::MushRoomScript::eDirection::Left:
			mAnimator->PlayAnimation(L"MushRoomLeftWalkR", true);
			break;
		case ME::MushRoomScript::eDirection::Right:
			mAnimator->PlayAnimation(L"MushRoomRightWalkL" ,true);
			break;
		case ME::MushRoomScript::eDirection::End:
			mAnimator->PlayAnimation(L"idleL", false);
			break;
		default:
			break;
		}
	}

	void MushRoomScript::LateUpdate()
	{
	}
	void MushRoomScript::Render(HDC hdc)
	{
	}
	void MushRoomScript::OnCollisionEnter(Collider* other)
	{
	}
	void MushRoomScript::OnCollisionStay(Collider* other)
	{
	}
	void MushRoomScript::OnCollisionExit(Collider* other)
	{
	}
}