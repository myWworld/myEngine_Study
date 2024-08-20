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


		switch (mState)
		{
		case ME::PlayerScript::eState::Standing:
			Standing();
			break;
		case ME::PlayerScript::eState::Attack:
			Attack();
			break;
		case ME::PlayerScript::eState::Jump:
			Jump();
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

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{
			
			if (Input::GetKey(eKeyCode::T))
			{
				mState = eState::Attack;
				mAnimator->PlayAnimation(L"RunnigAttackR");
			}

			mState = eState::Walk;
			mAnimator->PlayAnimation(L"RightWalkR");

		}


		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalkL");

		}

		if (Input::GetKey(eKeyCode::Down) || Input::GetKey(eKeyCode::S))
		{
			mState = eState::GetDown;
			mAnimator->PlayAnimation(L"GetDownR", false);
		}


		if (Input::GetKey(eKeyCode::Space) && isJump == false)
		{

			mState = eState::Jump;
			mAnimator->PlayAnimation(L"JumpR", false);

		}

		if (Input::GetKey(eKeyCode::T))
		{

		}

	}

	void PlayerScript::Move()
	{
		

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{
			if (Input::GetKey(eKeyCode::Shift))
			{
				mState = eState::Run;
				mAnimator->PlayAnimation(L"RunR", true);
			}

			mPrevDirection = ePrevDirection::Right;
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			mPrevDirection = ePrevDirection::Left;
			pos.x -= 100.0f * Time::DeltaTime();


			if (Input::GetKeyDown(eKeyCode::Space) && isJump == false)
			{
				mState = eState::Jump;
				mAnimator->PlayAnimation(L"JumpL",false);
			}

		}


		if ((Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
			&& Input::GetKey(eKeyCode::Shift))
		{
			mPrevDirection = ePrevDirection::Right;
			pos.x += 150.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Space) && isJump == false)
		{
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"JumpR", false);
		}

		tr->SetPosition(pos);

		if ((Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::D))
			|| (Input::GetKeyUp(eKeyCode::Left) || Input::GetKeyUp(eKeyCode::A))
			|| (Input::GetKeyUp(eKeyCode::Down) || Input::GetKeyUp(eKeyCode::S))
			|| (Input::GetKeyUp(eKeyCode::Space)))
		{
			mState = eState::Standing;

			PlayStandingAnimByPrevDirection();
		}
	}

	void PlayerScript::Jump()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();


		if (isJump == false)
		{
			isJump = true;
			pos.y -= 40.0f;
		}
		else if (isJump == true)
		{
			jumpSeconds += Time::DeltaTime();
			pos.y += 80.0f * Time::DeltaTime();

			if (jumpSeconds > 0.5f)
			{
				isJump = false;
				jumpSeconds = 0;
				
				mState = eState::Standing;
				PlayStandingAnimByPrevDirection();
			}
		
	
		}

		tr->SetPosition(pos);
	}

	void PlayerScript::Run()
	{

	}
	
	void PlayerScript::Attack()
	{
		
		if (Input::GetKeyUp(eKeyCode::T))
		{
			mState = eState::Move;
		}
	}
	
	void PlayerScript::PlayStandingAnimByPrevDirection()
	{
		if (mPrevDirection == ePrevDirection::Left)
		{
			mAnimator->PlayAnimation(L"StandingL");
		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			mAnimator->PlayAnimation(L"StandingR");
		}
	}
	

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hdc)
	{
	}
}


