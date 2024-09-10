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



		if (other->GetName() == L"Player")
		{
			if (mbIsBroken == false)
			{
				mbIsBroken = true;
				GetOwner()->GetComponent<Animator>()->PlayAnimation(L"UsedR", true);

				int prob = rand() % 8;
			
			if (prob < 3)
			{
				CreateStar(other);
			}
			else
			{
				CreateCoin(other);
			}
				
		}
			
			BoxCollider2D* qboxCol = GetOwner()->GetComponent<BoxCollider2D>();

			GameObject* player = other->GetOwner();

			Rigidbody* playerRb = player->GetComponent<Rigidbody>();
			Vector2 velocity = playerRb->GetVelocity();
			velocity.y = 50.0f;
			playerRb->SetVelocity(velocity);

			
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


	void QboxScript::CreateCoin(Collider* other)
	{
		GameObject* coin = object::Instantiate<GameObject>(enums::eLayerType::Items);

		BoxCollider2D* coinCol = coin->AddComponent<BoxCollider2D>();

		coin->AddComponent<CoinScript>();
		Rigidbody* coinRb = coin->AddComponent<Rigidbody>();

		coinRb->AddForce(Vector2(-200, -1500));

		coinCol->SetName(L"Coin");
		coinCol->SetOffset(Vector2(-55, -55));
		coinCol->SetSize(Vector2(0.2f, 0.2f));

		Animator* coinAnimator = coin->AddComponent<Animator>();

		coin->GetComponent<Transform>()->SetScale(Vector2(0.2f, 0.2f));

		Vector2 qboxPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();

		coin->GetComponent<Transform>()->SetPosition(Vector2(qboxPos.x + 20, qboxPos.y - 10));

		graphics::Texture* coinTex = Resources::Find<graphics::Texture>(L"COIN");

		coinAnimator->CreateAnimation(L"IdleR", coinTex, Vector2(0, 15), Vector2(120, 120), Vector2::Zero
			, 0.2f, 7, 6);

		coinAnimator->PlayAnimation(L"IdleR", true);
	}

	void QboxScript::CreateStar(Collider* other)
	{
		GameObject* star = object::Instantiate<GameObject>(enums::eLayerType::Items);
		BoxCollider2D* starCol = star->AddComponent<BoxCollider2D>();

		star->AddComponent<CoinScript>();
		Rigidbody* starRb = star->AddComponent<Rigidbody>();

		starRb->AddForce(Vector2(-200, -1500));

		starCol->SetName(L"Star");
		starCol->SetOffset(Vector2(-115, -115));
		starCol->SetSize(Vector2(0.2f, 0.2f));

		Animator* starAnimator = star->AddComponent<Animator>();

		star->GetComponent<Transform>()->SetScale(Vector2(0.1f, 0.1f));

		Vector2 qboxPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();

		star->GetComponent<Transform>()->SetPosition(Vector2(qboxPos.x + 90, qboxPos.y + 50 ));

		graphics::Texture* starTex = Resources::Find<graphics::Texture>(L"STAR");

		starAnimator->CreateAnimation(L"IdleR", starTex, Vector2(0, 0), Vector2(236, 236), Vector2::Zero
			, 0.2f, 13, 12);

		starAnimator->PlayAnimation(L"IdleR", true);
	}
}