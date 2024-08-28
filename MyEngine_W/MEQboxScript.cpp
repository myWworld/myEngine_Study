#include "MEQboxScript.h"

#include "MEInput.h"
#include "METransform.h"
#include "METime.h"
#include "MEGameObject.h"
#include "MEBulletScript.h"
#include "MEBullet.h"
#include "MEObject.h"
#include "MEResources.h"
#include "MEBoxCollider2D.h"
#include "MESceneManager.h"
#include "MEScenes.h"
#include "MERigidbody.h"
#include "MECoinScript.h"

#include "CommonInclude.h"

#include "MERenderer.h"
namespace ME
{



	ME::QboxScript::QboxScript()
		:mbIsBroken(false)
	{
	}

	ME::QboxScript::~QboxScript()
	{
	}

	void ME::QboxScript::Initialize()
	{
	}

	void ME::QboxScript::Update()
	{
	}

	void ME::QboxScript::LateUpdate()
	{
	}

	void ME::QboxScript::Render(HDC hdc)
	{
	}

	void ME::QboxScript::OnCollisionEnter(Collider* other)
	{



		if (other->GetName() == L"Player" && mbIsBroken == false)
		{
			mbIsBroken = true;

			other->GetOwner()->GetComponent<Rigidbody>()->AddForce(Vector2(0, 200));
			GetOwner()->GetComponent<Animator>()->PlayAnimation(L"UsedR", true);

			BoxCollider2D* qboxCol = GetOwner()->GetComponent<BoxCollider2D>();


			GameObject* coin = object::Instantiate<GameObject>(enums::eLayerType::Items);

			BoxCollider2D* coinCol = coin->AddComponent<BoxCollider2D>();
					
			coin->AddComponent<CoinScript>();
			Rigidbody* coinRb = coin->AddComponent<Rigidbody>();

			coinRb->AddForce(Vector2(-3000, -3000));

			coinCol->SetName(L"Item");
			coinCol->SetOffset(Vector2(-55, -55));
			coinCol->SetSize(Vector2(0.2f, 0.2f));

			Animator* coinAnimator = coin->AddComponent<Animator>();

			coin->GetComponent<Transform>()->SetScale(Vector2(0.2f, 0.2f));
			coin->GetComponent<Transform>()->SetPosition(Vector2(157, 366));

			graphics::Texture* coinTex = Resources::Find<graphics::Texture>(L"COIN");

			coinAnimator->CreateAnimation(L"IdleR", coinTex, Vector2(0, 15), Vector2(120, 120), Vector2::Zero
				, 0.2f, 7, 6);

			coinAnimator->PlayAnimation(L"IdleR", true);
		}
		else
		{

		}
	}

	void ME::QboxScript::OnCollisionStay(Collider* other)
	{
	}

	void ME::QboxScript::OnCollisionExit(Collider* other)
	{
	}

}