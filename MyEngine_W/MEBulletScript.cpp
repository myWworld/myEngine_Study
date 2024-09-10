#include "MEBulletScript.h"

#include "CommonInclude.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEResources.h"
#include "MEAnimator.h"

#include "MEMushRoomScript.h"
#include "MEMushRoom.h"

#include "MESkeleton.h"
#include "MESkeletonScript.h"


namespace ME
{
	BulletScript::BulletScript()
		:mbIsPlayerRunning(false)
	{
	}
	BulletScript::~BulletScript()
	{
		
	}
	void BulletScript::Initialize()
	{	
	

	}
	void BulletScript::Update()
	{
		Bullet* bullet = static_cast<Bullet*>(GetOwner());

		float time = bullet->GetBullletLastTime();


			if (2.0f < time)
			{
				bullet->SetActive(false);
				
				bullet->SetDeath();
			}

			MoveBulletByDirectionAndPlayerRunning();


			time += Time::DeltaTime();

			
			bullet->SetBulletTime(time);
		

	}

	void BulletScript::MoveBulletByDirectionAndPlayerRunning()
	{

		Bullet* bullet = static_cast<Bullet*>(GetOwner());

		Transform* tr = bullet->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (bullet->GetDirection() == Bullet::eDirection::Left)
		{
			if (mbIsPlayerRunning == true)
			{
				pos.x -= 240.0f * Time::DeltaTime();
			}
			else
			{
				pos.x -= 150.0f * Time::DeltaTime();
			}
		}
		else if (bullet->GetDirection() == Bullet::eDirection::Right)
		{
			if (mbIsPlayerRunning == true)
			{
				pos.x += 240.0f * Time::DeltaTime();
			}
			else
			{
				pos.x += 150.0f * Time::DeltaTime();
			}
		}
	

		tr->SetPosition(pos);
	}


	void BulletScript::LateUpdate()
	{
	}
	void BulletScript::Render(HDC hdc)
	{
	}
	void BulletScript::Destroy()
	{
	}
	void BulletScript::OnCollisionEnter(Collider* other)
	{
	
		if (other->GetName() == L"Mushroom")
		{
			MushRoom* monster = static_cast<MushRoom*>(other->GetOwner());
			MushRoomScript* script = monster->GetComponent<MushRoomScript>();
			Animator* animator = monster->GetComponent<Animator>();

			MushRoomScript::eDirection direction = script->GetDirection();

			
			if (script->GetHp() > 0)
			{

				if (direction == MushRoomScript::eDirection::Left)
				{
					animator->PlayAnimation(L"HurtL", false);
				}
				else if (direction == MushRoomScript::eDirection::Right)
				{
					animator->PlayAnimation(L"HurtR", false);
				}
			}
			else
			{
				return;

			}
				
		}

		if (other->GetName() == L"Skeleton")
		{	
			
			Skeleton* monster = static_cast<Skeleton*>(other->GetOwner());

			Animator* animator = monster->GetComponent<Animator>();
			SkeletonScript* script = monster->GetComponent<SkeletonScript>();

			SkeletonScript::eDirection direction = script->GetDirection();

			if (script->GetHp() != 0)
			{
				if (direction == SkeletonScript::eDirection::Left)
				{
					animator->PlayAnimation(L"HurtL", false);
				}
				else if (direction == SkeletonScript::eDirection::Right)
				{
					animator->PlayAnimation(L"HurtR", false);
				}
			}
			else
			{
				return;

			}
		}


	}
	void BulletScript::OnCollisionStay(Collider* other)
	{
	}
	void BulletScript::OnCollisionExit(Collider* other)
	{
	}
}