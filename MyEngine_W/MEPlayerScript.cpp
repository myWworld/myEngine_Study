#include "MEPlayerScript.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEAudioSource.h"
#include "MEAudioClip.h"

#include "MEGameObject.h"

#include "MEBulletScript.h"
#include "MEBullet.h"
#include "MEObject.h"
#include "MEResources.h"
#include "MEBoxCollider2D.h"
#include "MESceneManager.h"
#include "MEScenes.h"
#include "MERigidbody.h"

#include "CommonInclude.h"

#include "MERenderer.h"

namespace ME
{
	int PlayerScript::mScore = 0;
	float PlayerScript::mHp = 100.0f;
	bool PlayerScript::mbIsStar = false;

	PlayerScript::PlayerScript()
		:isJump(false)
		, jumpSeconds(0)
		, mState(PlayerScript::eState::Standing)
		, mAnimator(nullptr)
		, mEffect(nullptr)
		, mStarTime(0.0f)
		, mAttackTime(0.0f)
		, mbIsRunningAttack(false)
		, mbStillStartTime(false)	
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

		if (mHp == 0)
		{
			mState = eState::Die;
		}

		if (mbIsStar == true)
		{
			mStarTime += Time::DeltaTime();
			PlayAuraAnimation();

			if (mStarTime > 10.0f)
			{
				mStarTime = 0.0f;
				mbIsStar = false;
				mEffect->SetDeath();
			}
		}


		switch (mState)
		{
		case ME::PlayerScript::eState::Standing:
			Standing();
			break;
		case ME::PlayerScript::eState::StandAttack:
			StandingAttack();
			break;
		case ME::PlayerScript::eState::RunningAttack:
			RunningAttack();
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
		case ME::PlayerScript::eState::Die:
			Die();
			break;
		default:
			break;
		}


	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hdc)
	{
		PrintScore(hdc);
	}


	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == enums::eLayerType::Monster)
		{
			GameObject* monster = other->GetOwner();
			
			if (mbIsStar == true)
			{
				Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();

				Vector2 velocity = rb->GetVelocity();
				velocity.y = -300.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
			
				if (other->GetName() == L"Cannon")
				{
					rb->SetNeedGravity(true);
				}

				return;
			}

			if (mHp != 0)
			{
				mHp -= 10;

				Transform* MonsterTr = monster->GetComponent<Transform>();
				Transform* tr = GetOwner()->GetComponent<Transform>();
				Rigidbody *rb = GetOwner()->GetComponent<Rigidbody>();

				Vector2 pos = tr->GetPosition();

				Vector2 playerPos = tr->GetPosition() + GetOwner()->GetComponent<Collider>()->GetOffset();
				Vector2 monsterPos =MonsterTr->GetPosition() + other->GetOffset();

				Vector2 playerColliderSize = GetOwner()->GetComponent<Collider>()->GetSize() * 100.0f;
				Vector2 monsterColliderSize = other->GetSize() * 100.0f;
				
				Vector2 playerCenterPos = playerPos + (playerColliderSize / 2.0f);
				Vector2 monsterCenterPos = monsterPos + (monsterColliderSize / 2.0f);

				Vector2 leftOrRight = playerCenterPos - monsterCenterPos;

				if (leftOrRight.x >= 0)
				{
					if (mPrevDirection == ePrevDirection::Left)
					{

						mAnimator->PlayAnimation(L"HurtL", false);

					}
					else if (mPrevDirection == ePrevDirection::Right)
					{
						mAnimator->PlayAnimation(L"HurtR", false);

					}
				
					Vector2 velocity = rb->GetVelocity();
					velocity.x = 100.0f;
					rb->SetVelocity(velocity);
				}
				else
				{
					if (mPrevDirection == ePrevDirection::Left)
					{

						mAnimator->PlayAnimation(L"HurtL", false);

					}
					else if (mPrevDirection == ePrevDirection::Right)
					{
						mAnimator->PlayAnimation(L"HurtR", false);

					}
				
					Vector2 velocity = rb->GetVelocity();
					velocity.x = -100.0f;
					rb->SetVelocity(velocity);
				}

			

				tr->SetPosition(pos);

				mState = eState::Standing;
				PlayStandingAnimByPrevDirection();
			}
			else if(mHp == 0)
				return;
		}

		if (other->GetName() == L"Star")
		{

			if (mbIsStar == true)
			{
				mStarTime = 0.0f;
			}
			else
			{
				mbIsStar = true;
				mEffect = CreateAura();
			}
	
	
		}

		
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
		
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{
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

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (Input::GetKey(eKeyCode::Space) && rb->IsGround())
		{

			mState = eState::Jump;
			mAnimator->PlayAnimation(L"JumpR", false);

		}

		if (Input::GetKey(eKeyCode::T))
		{
			mState = eState::StandAttack;

			if (mPrevDirection == ePrevDirection::Left)
				mAnimator->PlayAnimation(L"StandAttackL");

			if (mPrevDirection == ePrevDirection::Right)
				mAnimator->PlayAnimation(L"StandAttackR");
		}

	}

	void PlayerScript::Move()
	{


		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();


		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{



			mPrevDirection = ePrevDirection::Right;

			pos += Vector2::Right * (90 * Time::DeltaTime());

			if (Input::GetKey(eKeyCode::Shift))
			{
				mState = eState::Run;
				mAnimator->PlayAnimation(L"RunR");
			}


			if (Input::GetKey(eKeyCode::T))
			{
				mState = eState::RunningAttack;
				mAnimator->PlayAnimation(L"RunningAttackR");
			}


		}

		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			mPrevDirection = ePrevDirection::Left;

			pos += Vector2::Left * (90 * Time::DeltaTime());

			if (Input::GetKey(eKeyCode::Shift))
			{
				mState = eState::Run;
				mAnimator->PlayAnimation(L"RunL");
			}

			if (Input::GetKey(eKeyCode::T))
			{
				mState = eState::RunningAttack;
				mAnimator->PlayAnimation(L"RunningAttackL");
			}

		}


		if (Input::GetKey(eKeyCode::Space) && rb->IsGround())
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
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		AudioSource* as = GetOwner()->GetComponent<AudioSource>();
		AudioClip* ac = GetOwner()->GetComponent<AudioClip>();
		ac = Resources::Find<AudioClip>(L"MARIOJUMPSOUND");

		if (ac == nullptr)
			return;

		as->SetClip(ac);

		if (as == nullptr)
			return;

		as->Play();

		Vector2 velocity = rb->GetVelocity();
		velocity.y = -300.0f;
		rb->SetVelocity(velocity);

		rb->SetGround(false);


		mState = eState::Standing;

	}

	void PlayerScript::Run()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();


		if (mPrevDirection == ePrevDirection::Left)
		{
			pos += Vector2::Left * (130 * Time::DeltaTime());
		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			pos += Vector2::Right * (130 * Time::DeltaTime());
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

	void PlayerScript::Die()
	{
		GetOwner()->SetActive(false);
		GetOwner()->SetDeath();

		renderer::mainCamera->SetTarget(nullptr);


		SceneManager::LoadScene(L"GameOverScene");
	}

	void PlayerScript::StandingAttack()
	{
		if (Input::GetKeyUp(eKeyCode::T))
		{
			mState = eState::Standing;
			PlayStandingAnimByPrevDirection();
		}
		if (Input::GetKey(eKeyCode::A) || Input::GetKey(eKeyCode::D))
		{
			mState = eState::RunningAttack;


			if (Input::GetKey(eKeyCode::A))
			{
				mAnimator->PlayAnimation(L"RunningAttackL");
			}

			if (Input::GetKey(eKeyCode::D))
			{
				mAnimator->PlayAnimation(L"RunningAttackR");
			}
		}
	}

	void PlayerScript::RunningAttack()
	{

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Right) || Input::GetKey(eKeyCode::D))
		{
			mPrevDirection = ePrevDirection::Right;
			pos += Vector2::Right * (90 * Time::DeltaTime());
			RunAttackTime();

			if (Input::GetKey(eKeyCode::Space) && rb->IsGround())
			{

				mState = eState::Jump;
				mAnimator->PlayAnimation(L"JumpR", false);

			}
		}

		if (Input::GetKey(eKeyCode::Left) || Input::GetKey(eKeyCode::A))
		{
			mPrevDirection = ePrevDirection::Left;
			pos += Vector2::Left * (90 * Time::DeltaTime());
			RunAttackTime();

			if (Input::GetKey(eKeyCode::Space) && rb->IsGround())
			{

				mState = eState::Jump;
				mAnimator->PlayAnimation(L"JumpR", false);

			}
		}

		tr->SetPosition(pos);



		if (Input::GetKeyUp(eKeyCode::T))
		{
			mState = eState::Standing;
			PlayStandingAnimByPrevDirection();
		}

		if (Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::D))
		{
			mState = eState::StandAttack;

			if (mPrevDirection == ePrevDirection::Left)
				mAnimator->PlayAnimation(L"StandAttackL");

			if (mPrevDirection == ePrevDirection::Right)
				mAnimator->PlayAnimation(L"StandAttackR");
		}

	}

	void PlayerScript::MakeBullet(bool isRunning)
	{
		GameObject* bullet = object::Instantiate<Bullet>(enums::eLayerType::Particle);

		BulletScript* bulletScript = bullet->AddComponent<BulletScript>();
		bulletScript->SetPlayerIsRunningAttack(isRunning);

		Animator* bulletAnim = bullet->AddComponent<Animator>();

		BoxCollider2D* bulletCollider = bullet->AddComponent<BoxCollider2D>();
		bulletCollider->SetName(L"Bullet");

		bulletCollider->SetSize(Vector2(0.05f, 0.05f));
		bulletCollider->SetOffset(Vector2(-17, -20));

		graphics::Texture* bulletRightTex = Resources::Find<graphics::Texture>(L"BULLETR");
		graphics::Texture* bulletLeftTex = Resources::Find<graphics::Texture>(L"BULLETL");


		Transform* bulletTr = bullet->GetComponent<Transform>();

		Transform* playerTr = GetOwner()->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();

		Vector2 bulletPos = Vector2::Zero;

		bulletAnim->CreateAnimation(L"BulletR", bulletRightTex, Vector2(0, 0)
			, Vector2(50, 50), Vector2(0, 0), 0.3f, 1);
		bulletAnim->CreateAnimation(L"BulletL", bulletLeftTex, Vector2(0, 0)
			, Vector2(50, 50), Vector2(0, 0), 0.3f, 1);

		if (mPrevDirection == ePrevDirection::Left)
		{
			bulletPos = playerTr->GetPosition() + Vector2(-10, 8);
		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			bulletPos = playerTr->GetPosition() + Vector2(26, 8);
		}

		bulletTr->SetPosition(bulletPos);
		bulletTr->SetScale(Vector2(0.3f, 0.3f));

		PlayBulletByPrveDirection(bulletAnim);

	}

	void PlayerScript::RunAttackTime()
	{
		mAttackTime += Time::DeltaTime();

		if (mAttackTime > 0.4f)
		{
			MakeBullet(true);
			mAttackTime = 0.0f;
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

	void PlayerScript::PlayBulletByPrveDirection(Animator* animator)
	{
		Bullet* obj = static_cast<Bullet*>(animator->GetOwner());


		if (mPrevDirection == ePrevDirection::Left)
		{
			animator->PlayAnimation(L"BulletL", true);
			obj->SetDirection(Bullet::eDirection::Left);

		}
		else if (mPrevDirection == ePrevDirection::Right)
		{
			animator->PlayAnimation(L"BulletR", true);
			obj->SetDirection(Bullet::eDirection::Right);
		}
	}


	void PlayerScript::PrintScore(HDC hdc)
	{
		std::wstring wstr = std::to_wstring(mScore);


		HFONT hfont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("jejufont"));
		HFONT oldfond = (HFONT)SelectObject(hdc, (HFONT)hfont);

		SelectObject(hdc, oldfond);
		DeleteObject(hfont);

		wchar_t str[50];
		wcsncpy_s(str, wstr.c_str(), 5);

		SetTextColor(hdc, 0x0000FF00);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 700, 0, str, wcslen(str));

	}
	void PlayerScript::PlayAuraAnimation()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mEffect == nullptr)
			return;

		Animator* effectAnimator = mEffect->GetComponent<Animator>();

		Transform* effectTr = mEffect->GetComponent<Transform>();
		
		effectTr->SetPosition(Vector2(pos.x + 50, pos.y + 50));
		effectTr->SetScale(Vector2(0.4f, 0.4f));

		
		effectAnimator->PlayAnimation(L"StarEffectR");
	}

	GameObject* PlayerScript::CreateAura()
	{
		GameObject* effect = object::Instantiate <GameObject> (enums::eLayerType::Aura);

		Animator* effectAnimator = effect->AddComponent<Animator>();

		graphics::Texture* effectTex = Resources::Find<graphics::Texture>(L"STAREFFECT");

		effectAnimator->CreateAnimation(L"StarEffectR", effectTex, Vector2(0, 0), Vector2(196, 212), Vector2::Zero
			, 0.01f, 5);

		return effect;
	}
}


