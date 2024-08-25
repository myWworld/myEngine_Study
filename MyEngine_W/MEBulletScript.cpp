#include "MEBulletScript.h"

#include "CommonInclude.h"
#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEResources.h"
#include "MEAnimator.h"




namespace ME
{
	BulletScript::BulletScript()
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

		Transform* tr = bullet->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

			if (2.0f < time)
			{
				bullet->SetActive(false);
				
				bullet->Death();
			}

			if (bullet->GetDirection() == Bullet::eDirection::Left)
			{
				pos.x -= 150.0f * Time::DeltaTime();
			}
			else if(bullet->GetDirection() == Bullet::eDirection::Right)
				pos.x += 150.0f * Time::DeltaTime();


			time += Time::DeltaTime();

			
			bullet->SetBulletTime(time);
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
	}
	void BulletScript::OnCollisionStay(Collider* other)
	{
	}
	void BulletScript::OnCollisionExit(Collider* other)
	{
	}
}