#include "MEFloorScript.h"
#include "MERigidbody.h"
#include "MEGameObject.h"
#include "METransform.h"
#include "MECollider.h"
#include "MEInput.h"

namespace ME
{
	FloorScript::FloorScript()
		:mbIsOnFloor(false)
	{
	}
	FloorScript::~FloorScript()
	{
	}
	void FloorScript::Initialize()
	{
	}
	void FloorScript::Update()
	{

	}
	void FloorScript::LateUpdate()
	{
	}
	void FloorScript::Render(HDC hdc)
	{
	}
	void FloorScript::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == enums::eLayerType::Player
			 || other->GetOwner()->GetLayerType() == enums::eLayerType::Items
			   || other->GetOwner()->GetLayerType() == enums::eLayerType::Monster)
		{
			CannotPass(other);
		}
	}
	void FloorScript::OnCollisionStay(Collider* other)
	{

		if (other->GetName() == L"Player")
		{
			Rigidbody* playerRb = other->GetOwner()->GetComponent<Rigidbody>();

			if (Input::GetKey(eKeyCode::Space))
				mbIsOnFloor = false;
		}

		if (mbIsOnFloor == true)
			CannotPass(other);
	
	}
	void FloorScript::OnCollisionExit(Collider* other)
	{
		Rigidbody* playerRb = other->GetOwner()->GetComponent<Rigidbody>();
		mbIsOnFloor = false;
		playerRb->SetGround(false);
	}

	void FloorScript::CannotPass(Collider* obj)
	{
		Rigidbody* playerRb = obj->GetOwner()->GetComponent<Rigidbody>();
		Transform* playerTr = obj->GetOwner()->GetComponent<Transform>();
		Collider* playerCol = obj;

		Transform* floorTr = this->GetOwner()->GetComponent<Transform>();
		Rigidbody* floorRb = this->GetOwner()->GetComponent<Rigidbody>();
		Collider* floorCol = this->GetOwner()->GetComponent<Collider>();


		Vector2 playerColSize = playerCol->GetSize() * 100.0f;
		Vector2 floorColSize = floorCol->GetSize() * 100.0f;

		Vector2 playerCenterPos = (playerTr->GetPosition() + playerCol->GetOffset()) + playerColSize / 2.0f;
		Vector2 floorCenterPos = (floorTr->GetPosition() + floorCol->GetOffset()) + floorColSize / 2.0f;

		float floorTop = floorCenterPos.y - (floorColSize.y / 2.0f);

		if (playerCenterPos.y > floorTop)
			return;
	
		
		float len = fabs(playerCenterPos.y - floorCenterPos.y);
		float scale = fabs(playerColSize.y / 2.0f + floorColSize.y / 2.0f);

		if (len < scale)
		{
			Vector2 playerPos = playerTr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;

			mbIsOnFloor = true;
			playerTr->SetPosition(playerPos);
		}


		playerRb->SetGround(true);
	}
}