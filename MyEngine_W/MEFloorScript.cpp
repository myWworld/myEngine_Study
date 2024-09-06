#include "MEFloorScript.h"
#include "MERigidbody.h"
#include "MEGameObject.h"
#include "METransform.h"
#include "MECollider.h"

namespace ME
{
	FloorScript::FloorScript()
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
			Rigidbody* playerRb = other->GetOwner()->GetComponent<Rigidbody>();
			Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
			Collider* playerCol = other;

			Transform* floorTr =this-> GetOwner()->GetComponent<Transform>();
			Rigidbody* floorRb = this->GetOwner()->GetComponent<Rigidbody>();
			Collider* floorCol = this->GetOwner()->GetComponent<Collider>();


			Vector2 playerColSize = playerCol->GetSize() * 100.0f;
			Vector2 floorColSize = floorCol->GetSize() * 100.0f;

			Vector2 playerCenterPos = (playerTr->GetPosition() + playerCol->GetOffset()) + playerColSize/2.0f;
			Vector2 floorCenterPos = (floorTr->GetPosition() + floorCol->GetOffset()) + floorColSize / 2.0f;

	

			float len = fabs(playerCenterPos.y - floorCenterPos.y);
			float scale = fabs(playerColSize.y /2.0f + floorColSize.y / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = playerTr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;

				playerTr->SetPosition(playerPos);
			}


			playerRb->SetGround(true);
		}
	}
	void FloorScript::OnCollisionStay(Collider* other)
	{
	}
	void FloorScript::OnCollisionExit(Collider* other)
	{
	}
}