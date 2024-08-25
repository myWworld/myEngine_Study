#include "MEPlayerScript.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEGameObject.h"
#include "MEBulletScript.h"
#include "MEBullet.h"
#include "MEObject.h"
#include "MEResources.h"

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
			Run();
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
			
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"RightWalkR");

		}


		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			
			mState = eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalkL");

		}


		if (Input::GetKey(eKeyCode::Space) && isJump == false)
		{

			mState = eState::Jump;
			mAnimator->PlayAnimation(L"JumpR", false);

		}

		if (Input::GetKey(eKeyCode::T))
		{
			mState = eState::Attack;
			if(mPrevDirection == ePrevDirection::Left)
				mAnimator->PlayAnimation(L"StandAttackL");

			if (mPrevDirection == ePrevDirection::Right)
				mAnimator->PlayAnimation(L"StandAttackR");
		}

	}

	void PlayerScript::Move()
	{
		

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{

			mPrevDirection = ePrevDirection::Right;
			pos.x += 100.0f * Time::DeltaTime();

			if (Input::GetKey(eKeyCode::Shift))
			{
				mState = eState::Run;
				mAnimator->PlayAnimation(L"RunR");
			}


			if (Input::GetKey(eKeyCode::T))
			{
				mState = eState::Attack;

				mAnimator->PlayAnimation(L"RunningAttackR");
			}

		
		}

		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
				mPrevDirection = ePrevDirection::Left;
			pos.x -= 100.0f * Time::DeltaTime();

			if (Input::GetKey(eKeyCode::Shift))
			{
				mState = eState::Run;
				mAnimator->PlayAnimation(L"RunL");
			}

			if (Input::GetKey(eKeyCode::T))
			{
				mState = eState::Attack;
				mAnimator->PlayAnimation(L"RunningAttackL");
			}

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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();


		if (mPrevDirection == ePrevDirection::Left)
		{
			pos += Vector2::Left * (130.0f * Time::DeltaTime());
		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			pos += Vector2::Right * (130.0f * Time::DeltaTime());
		}
		
		tr->SetPosition(pos);

		if ((Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::D))
			|| (Input::GetKeyUp(eKeyCode::Left) || Input::GetKeyUp(eKeyCode::A))
			|| Input::GetKeyUp(eKeyCode::Shift))
		{
			mState = eState::Standing;
			PlayStandingAnimByPrevDirection();
		}
	}
	
	void PlayerScript::Attack()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		
		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{
			mPrevDirection = ePrevDirection::Right;
			pos += Vector2::Right * (130 * Time::DeltaTime());
			
			if(mAnimator->IsComplete())
				mAnimator->PlayAnimation(L"RunningAttackR");
		}
		else if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			mPrevDirection = ePrevDirection::Right;
			pos += Vector2::Left * (130 * Time::DeltaTime());
			
			if (mAnimator->IsComplete())
				mAnimator->PlayAnimation(L"RunningAttackL");

		}
		
		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::T)) 
		{
			mState = eState::Standing;
			PlayStandingAnimByPrevDirection();
		}

	}

	void PlayerScript::MakeBullet()
	{
		GameObject* bullet = object::Instantiate<Bullet>(enums::eLayerType::Particle);

		bullet->AddComponent<BulletScript>();
		Animator* bulletAnim = bullet->AddComponent<Animator>();

		graphics::Texture* bulletRightTex = Resources::Find<graphics::Texture>(L"BULLETR");
		graphics::Texture* bulletLeftTex = Resources::Find<graphics::Texture>(L"BULLETL");


		Transform* bulletTr = bullet->GetComponent<Transform>();

		Transform* playerTr = GetOwner()->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();

		Vector2 bulletPos = Vector2::Zero;

		bulletAnim->CreateAnimation(L"BulletR", bulletRightTex, Vector2(0, 0)
			, Vector2(50, 50), Vector2(0, 0), 0.3f, 1);
		bulletAnim->CreateAnimation(L"BulletL", bulletLeftTex, Vector2(0, 0)
			, Vector2(50, 50), Vector2(20, 0), 0.3f, 1);

		if (mPrevDirection == ePrevDirection::Left)
		{
			bulletPos = playerTr->GetPosition() + Vector2(-27, 8);
		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			bulletPos = playerTr->GetPosition() + Vector2(26, 8);
		}

		bulletTr->SetPosition(bulletPos);
		bulletTr->SetScale(Vector2(0.3f, 0.3f));

		PlayBulletByPrveDirection(bulletAnim);

		mState = eState::Standing;

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

	void PlayerScript::PlayBulletByPrveDirection(Animator *animator)
	{
		Bullet* obj = static_cast<Bullet*>(animator->GetOwner());
		

		if (mPrevDirection == ePrevDirection::Left)
		{
			animator->PlayAnimation(L"BulletL",true);
			obj->SetDirection(Bullet::eDirection::Left);
			
		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			animator->PlayAnimation(L"BulletR",true);
			obj->SetDirection(Bullet::eDirection::Right);
		}
	}
	

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hdc)
	{
	}
}


