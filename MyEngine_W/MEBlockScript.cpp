#include "MEBlockScript.h"
#include "MEResource.h"
#include "MEScenes.h"
#include "MEInput.h"
#include "MEGameOverScene.h"
#include "MESceneManager.h"
#include "METransform.h"
#include "CommonInclude.h"
#include "MECollider.h"
#include "MEBoxCollider2D.h"
#include "MERigidbody.h"

namespace ME
{


	ME::BlockScript::BlockScript()
		:mbIsOnBlock(false)
	{
	}

	ME::BlockScript::~BlockScript()
	{
	}

	void ME::BlockScript::Initialize()
	{
	}

	void ME::BlockScript::Update()
	{
	}

	void ME::BlockScript::LateUpdate()
	{
	}

	void ME::BlockScript::Render(HDC hdc)
	{
	}

	void ME::BlockScript::OnCollisionEnter(Collider* other)
	{
		if (other->GetName() == L"Cannon")
			return;

		CannotMove(other);

	}

	void ME::BlockScript::OnCollisionStay(Collider* other)
	{
	}

	void ME::BlockScript::OnCollisionExit(Collider* other)
	{
		Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();

		if (mbIsOnBlock == true)
		{
			rb->SetGround(false);
			mbIsOnBlock = false;
		}
	}

	void BlockScript::CannotMove(Collider *obj)
	{
		Rigidbody* playerRb = obj->GetOwner()->GetComponent<Rigidbody>();
		Transform* playerTr = obj->GetOwner()->GetComponent<Transform>();
		Collider* playerCol = obj;

		Transform* ChimneyTr = this->GetOwner()->GetComponent<Transform>();
		Vector2 ChimneyPos = ChimneyTr->GetPosition();

		Rigidbody* ChimneyRb = this->GetOwner()->GetComponent<Rigidbody>();
		Collider* ChimneyCol = this->GetOwner()->GetComponent<Collider>();


		Vector2 playerColSize = playerCol->GetSize() * 100.0f;
		Vector2 ChimneyColSize = ChimneyCol->GetSize() * 100.0f;

		Vector2 playerCenterPos = (playerTr->GetPosition() + playerCol->GetOffset()) + playerColSize / 2.0f;
		Vector2 ChimneyCenterPos = (ChimneyTr->GetPosition() + ChimneyCol->GetOffset()) + ChimneyColSize / 2.0f;

		float playerBottom = playerCenterPos.y + (playerColSize.y / 2.0f);
		float chimneyTop = ChimneyCenterPos.y - (ChimneyColSize.y / 2.0f);

		if (fabs(playerBottom - chimneyTop) <= 8)
		{
			float len = fabs(playerCenterPos.y - ChimneyCenterPos.y);
			float scale = fabs(playerColSize.y / 2.0f + ChimneyColSize.y / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = playerTr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;

				playerTr->SetPosition(playerPos);
				mbIsOnBlock = true;
			}


			playerRb->SetGround(true);

		}
		else
		{
			float direct = playerCenterPos.x - ChimneyCenterPos.x;
			Vector2 playerPos = playerTr->GetPosition();

			if (direct <= 0)
			{
				playerPos.x -= 3.0f;
			}
			else
			{
				playerPos.x += 3.0f;

			}

			playerTr->SetPosition(playerPos);
		}

	}

}