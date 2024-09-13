#include "MECannoScript.h"
#include "MERigidbody.h"
#include "METransform.h"
#include "METime.h"

#include "MEPlayerScript.h"

namespace ME
{
	CannonScript::CannonScript()
		:mbIsBumpedWhenStarIsOn(false)
	{
	}
	CannonScript::~CannonScript()
	{
	}
	void CannonScript::Initialize()
	{
	}
	void CannonScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (pos.x < 0)
		{
			GetOwner()->SetDeath();
		}

		if (mbIsBumpedWhenStarIsOn == true)
		{
			pos.x -= 100 * Time::DeltaTime();
			pos.y -= 100 * Time::DeltaTime();
		}
		else
			pos.x -= 100 * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	void CannonScript::LateUpdate()
	{
	}
	void CannonScript::Render(HDC hdc)
	{
	}
	void CannonScript::Destroy()
	{
	}
	void CannonScript::OnCollisionEnter(Collider* other)
	{
		if (other->GetName() == L"Player")
		{
			if (PlayerScript::IsStar() == true)
			{
				mbIsBumpedWhenStarIsOn = true;
				return;
			}

			if (FlagScript::IsOnFlag() == true)
			{
				return;
			}

			GameObject* player = other->GetOwner();

			Rigidbody *playerRb = player->GetComponent<Rigidbody>();

			Vector2 velocity = playerRb->GetVelocity();
			velocity.x = -100.0f;
			velocity.y = -800.0f;

			playerRb->SetVelocity(velocity);

			playerRb->SetGround(false);
		}
	}

	void CannonScript::OnCollisionStay(Collider* other)
	{
	}
	void CannonScript::OnCollisionExit(Collider* other)
	{
	}
}