#include "MECannoScript.h"
#include "MERigidbody.h"
#include "METransform.h"
#include "METime.h"

#include "MEPlayerScript.h"

namespace ME
{
	CannonScript::CannonScript()
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
			if (PlayerScript::IsStar())
				return; 

			GameObject* player = other->GetOwner();

			Rigidbody *playerRb = player->GetComponent<Rigidbody>();

			Vector2 velocity = playerRb->GetVelocity();
			velocity.x = -1000.0f;
			velocity.y = -600.0f;

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