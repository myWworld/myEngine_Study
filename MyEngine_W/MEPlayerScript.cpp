#include "MEPlayerScript.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEGameObject.h"
#include "MEAnimator.h"


namespace ME
{
	PlayerScript::PlayerScript()
		:isJump(false)
		, jumpSeconds(0)
		, mState(PlayerScript::eState::Standing)
		, mAnimator(nullptr)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{

	}
	void PlayerScript::Update()
	{

		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		if (isJump == true)
		{
			jumpSeconds++;

			if (jumpSeconds > 30)
			{
				jumpSeconds = 0;
				isJump = false;
				Transform* tr = GetOwner()->GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y += 100 * Time::DeltaTime();
			}
		}

		switch (mState)
		{
		case ME::PlayerScript::eState::Standing:
			Standing();
			break;
		case ME::PlayerScript::eState::Attack:
			Attack();
			break;
		case ME::PlayerScript::eState::Jump:
			Move();
			break;
		case ME::PlayerScript::eState::Run:
			Move();
			break;
		case ME::PlayerScript::eState::Walk:
			Move();
			break;
		case ME::PlayerScript::eState::Fall:
			Move();
			break;
		case ME::PlayerScript::eState::GetDown:
			Move();
			break;
		default:
			break;
		}


	}

	void PlayerScript::Standing()
	{
		mPrevState = eState::Standing;

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{
			if (Input::GetKey(eKeyCode::Shift))
			{
				mState = eState::Run;
				mAnimator->PlayAnimation(L"Run");
			}

			if (Input::GetKey(eKeyCode::T))
			{
				mState = eState::Attack;
				mAnimator->PlayAnimation(L"RunnigAttack");
			}

			mState = eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");

		}


		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalk");
		}

		if (Input::GetKey(eKeyCode::Down) || Input::GetKey(eKeyCode::S))
		{
			mState = eState::GetDown;
			mAnimator->PlayAnimation(L"GetDown", false);
		}

		if (Input::GetKeyDown(eKeyCode::Space) && isJump == false)
		{
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"Jump", false);

		}

		if (Input::GetKey(eKeyCode::T))
		{

			if (mPrevState == eState::Standing)
			{
				mAnimator->PlayAnimation(L"StandAttack");
				mState = eState::Standing;
			}
		}

	}

	void PlayerScript::Move()
	{
		mPrevState = eState::Move;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{

			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{

			pos.x -= 100.0f * Time::DeltaTime();

		}


		if ((Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
			&& Input::GetKey(eKeyCode::Shift))
		{

			pos.x += 150.0f * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::Space) && isJump == false)
		{

			isJump = true;
			mAnimator->PlayAnimation(L"Jump");

			pos.y -= 200.0f * Time::DeltaTime();


		}


		//
		 //if (Input::GetKey(eKeyCode::Shift))
		 //{
		 //
		 //	mAnimator->PlayAnimation(L"BulletEffect");
		//
		 //}
		//

		tr->SetPosition(pos);

		if ((Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::D))
			|| (Input::GetKeyUp(eKeyCode::Left) || Input::GetKeyUp(eKeyCode::A))
			|| (Input::GetKeyUp(eKeyCode::Down) || Input::GetKeyUp(eKeyCode::S))
			|| (Input::GetKeyUp(eKeyCode::Space)))
		{
			mState = eState::Standing;
			mAnimator->PlayAnimation(L"Standing", true);
		}
	}

		void PlayerScript::Attack()
		{
			
			if (Input::GetKeyUp(eKeyCode::T))
			{
				mState = eState::Move;
			}
		}

		void PlayerScript::LateUpdate()
		{
		}
		void PlayerScript::Render(HDC hdc)
		{
		}
}


