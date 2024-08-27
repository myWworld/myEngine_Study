#include "MEPlayScene.h"
#include "MEGameObject.h"

#include "MEInput.h"
#include "METitleScene.h"
#include "MEObject.h"
#include "MEResources.h"

#include "MESceneManager.h"
#include "METransform.h"
#include "MESpriteRenderer.h"
#include "MEBoxCollider2D.h"
#include "MECamera.h"

#include "MERenderer.h"
#include "MEApplication.h"

#include "MEPlayer.h"
#include "MEPlayerScript.h"
#include "MEMushRoom.h"
#include "MEMushRoomScript.h"
#include "MESkeleton.h"
#include "MESkeletonScript.h"
#include "MEBullet.h"
#include "MEBulletScript.h"

#include "MECollisionManager.h"


extern ME::Application application;



namespace ME
{	
	

	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster,true);

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Particle, enums::eLayerType::Monster,true);


		Vector2 resolution = Vector2(application.GetWidth(), application.GetHeight());

		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, resolution / 2.0f);
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
			
				GameObject* bg = object::Instantiate<GameObject>
					(enums::eLayerType::BackGround, Vector2(0,200));

				SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
				bgSr->SetSize(Vector2(1.3f, 1.3f));


				graphics::Texture* map = Resources::Find<graphics::Texture>(L"STAGE1_1");
				bgSr->SetTexture(map);
			
			
				playerInitialize();

				GameObject* mushroom = object::Instantiate<MushRoom>(enums::eLayerType::Monster, Vector2(400, 425));

				MushRoomScript* mushroomScript = mushroom->AddComponent<MushRoomScript>();
				Animator* mushroomAnimator = mushroom->AddComponent<Animator>();

				BoxCollider2D* mushroomBoxCollider = mushroom->AddComponent<BoxCollider2D>();
				mushroomBoxCollider->SetName(L"Mushroom");

				mushroomBoxCollider->SetOffset(Vector2(-65, -65));
				mushroomBoxCollider->SetSize(Vector2(0.5f, 0.5f));


				mushroom->GetComponent<Transform>()->SetScale(Vector2(0.4f, 0.4f));
				graphics::Texture* mushroomLeftTex = Resources::Find<graphics::Texture>(L"MUSHROOML");
				graphics::Texture* mushroomRightTex = Resources::Find<graphics::Texture>(L"MUSHROOMR");

				CreateMushRoomAnimation(mushroomAnimator, mushroomRightTex, mushroomLeftTex);

				mushroomAnimator->GetCompleteEvent(L"DeadR") = std::bind(&MushRoomScript::Respawn, mushroomScript);

				mushroomAnimator->PlayAnimation(L"IdleL", false);
			

			
				GameObject* skeleton = object::Instantiate<Skeleton>(enums::eLayerType::Monster
					, Vector2(600, 406));

				BoxCollider2D* skeletonCollider = skeleton->AddComponent<BoxCollider2D>();
				skeletonCollider->SetName(L"Skeleton");

				skeletonCollider->SetOffset(Vector2(-34, -70));
				skeletonCollider->SetSize(Vector2(0.2f, 0.8f));


				SkeletonScript* skeletonScript = skeleton->AddComponent<SkeletonScript>();
				Animator* skeletonAnimator = skeleton->AddComponent<Animator>();
				skeleton->GetComponent<Transform>()->SetScale(Vector2(0.6f, 0.6f));

				graphics::Texture* skeletonLeftTex = Resources::Find<graphics::Texture>(L"SKELETONL");
				graphics::Texture* skeletonRightTex = Resources::Find<graphics::Texture>(L"SKELETONR");
				
				CreateSkeletonAnimation(skeletonAnimator, skeletonRightTex, skeletonLeftTex);


				skeletonAnimator->GetCompleteEvent(L"DeadL") = std::bind(&SkeletonScript::Respawn, skeletonScript);
				skeletonAnimator->GetCompleteEvent(L"DeadR") = std::bind(&SkeletonScript::Respawn, skeletonScript);


				skeletonAnimator->PlayAnimation(L"SkeletonIdleR",false);
			

			
			
		

		Scene::Initialize();
	}

	

	void PlayScene::Update()
	{
		Scene::Update();


	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"TitleScene");
		}

	//
	//if (playerPos.x > application.GetWidth() 
	//	|| playerPos.x < 0)
	//{
	//	SceneManager::LoadScene(L"GameOverScene");
	//}
	//
	//
	//if (playerPos.y < 0
	//	|| playerPos.y > application.GetHeight())
	//{
	//	SceneManager::LoadScene(L"GameOverScene");
	//}
	}

	void PlayScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
		wchar_t str[50] = L"PlayScene";
		TextOut(mHdc, 0, 0, str, 9);
	}

	void PlayScene::OnEnter()
	{
		playerInitialize();


	}
	void PlayScene::OnExit()
	{

	}

	void PlayScene::playerInitialize()
	{
		GameObject* mPlayer = object::Instantiate<Player>
			(enums::eLayerType::Player, Vector2(100, 406));

		renderer::mainCamera->SetTarget(mPlayer);

		PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();
		mPlayer->GetComponent<Transform>()->SetScale(Vector2(0.7f, 0.7f));

		BoxCollider2D* playerBoxCollider = mPlayer->AddComponent<BoxCollider2D>();
		playerBoxCollider->SetName(L"Player");

		playerBoxCollider->SetOffset(Vector2(-20, -20));
		playerBoxCollider->SetSize(Vector2(0.3f, 0.3f));

		//	object::DontDestroyOnLoad(mPlayer);

		graphics::Texture* megamanRightTex = Resources::Find<graphics::Texture>(L"MEGAMANR");
		graphics::Texture* megamanLeftTex = Resources::Find<graphics::Texture>(L"MEGAMANL");

		Animator* animator = mPlayer->AddComponent<Animator>();


		CreatePlayerAnimation(animator, megamanRightTex, megamanLeftTex);
		animator->PlayAnimation(L"StandingR", true);


		animator->GetCompleteEvent(L"StandAttackL") = std::bind(&PlayerScript::MakeBullet, playerScript);
		animator->GetCompleteEvent(L"RunningAttackL") = std::bind(&PlayerScript::MakeBullet, playerScript);

		animator->GetCompleteEvent(L"StandAttackR") = std::bind(&PlayerScript::MakeBullet, playerScript);
		animator->GetCompleteEvent(L"RunningAttackR") = std::bind(&PlayerScript::MakeBullet, playerScript);
		//				animator->GetStartEvent(L"RunningAttackR") = std::bind(&PlayerScript::MakeBullet, playerScript);

	}

	void PlayScene::CreatePlayerAnimation(Animator* animator
		,graphics::Texture* Rtexture
		,graphics::Texture* Ltexture)
	{
		animator->CreateAnimation(L"RightWalkR", Rtexture, Vector2(0, 212.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.1f, 8, 3);
		animator->CreateAnimation(L"LeftWalkL", Ltexture, Vector2(356, 212.0f), Vector2(50, 50), Vector2(0, 0), 0.1f, 8, 3);

		animator->CreateAnimation(L"RunR", Rtexture, Vector2(0, 212.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.07f, 8, 3);
		animator->CreateAnimation(L"RunL", Ltexture, Vector2(356, 212), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.07f, 8,3);

		animator->CreateAnimation(L"JumpR", Rtexture, Vector2(0, 412), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.1f, 7);
		animator->CreateAnimation(L"JumpL", Ltexture, Vector2(356, 412), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.1f, 7);

		animator->CreateAnimation(L"StandingR", Rtexture, Vector2(301.0f, 10.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.3f, 2, 8);
		animator->CreateAnimation(L"StandingL", Ltexture, Vector2(55.0f, 10.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.3f, 2, 8);
		
		animator->CreateAnimation(L"StandAttackR", Rtexture, Vector2(0, 112), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3);
		animator->CreateAnimation(L"RunningAttackR", Rtexture, Vector2(245, 262), Vector2(50.0f, 50.0f), Vector2::Zero, 0.07f, 3, 8);

		animator->CreateAnimation(L"StandAttackL", Ltexture, Vector2(357, 112), Vector2(49.0f, 50.0f), Vector2::Zero, 0.1f, 3);
		animator->CreateAnimation(L"RunningAttackL", Ltexture, Vector2(356, 262), Vector2(50.0f, 50.0f), Vector2::Zero, 0.07f, 3, 8);

		animator->CreateAnimation(L"HurtL", Ltexture, Vector2(54, 162), Vector2(50.0f, 50.0f), Vector2::Zero, 0.05f, 2);
		animator->CreateAnimation(L"HurtR", Rtexture, Vector2(251, 162), Vector2(50.0f, 50.0f), Vector2::Zero, 0.05f, 2);
	}

	void PlayScene::CreateMushRoomAnimation(Animator* animator
		, graphics::Texture* Rtexture
		, graphics::Texture* Ltexture)
	{
		animator->CreateAnimation(L"MushRoomLeftWalkR", Ltexture, Vector2(0, 126.0f), Vector2(133.5f, 137), Vector2::Zero, 0.5f, 5);
		animator->CreateAnimation(L"MushRoomRightWalkL", Rtexture, Vector2(700, 126.0f), Vector2(133.5f, 137), Vector2::Zero, 0.5f, 5);
		animator->CreateAnimation(L"IdleL", Ltexture, Vector2(0, 0), Vector2(130, 130), Vector2::Zero, 0.2f, 1);

		animator->CreateAnimation(L"HurtL", Ltexture, Vector2(0, 395), Vector2(130, 150), Vector2::Zero, 0.02f, 1);
		animator->CreateAnimation(L"HurtR", Rtexture, Vector2(703, 395), Vector2(130, 150), Vector2::Zero, 0.02f, 1);

		animator->CreateAnimation(L"DeadR", Ltexture, Vector2(0, 1056), Vector2(202, 140), Vector2::Zero, 0.4f, 4, 2);
	}

	void PlayScene::CreateSkeletonAnimation(Animator* animator
		, graphics::Texture* Rtexture
		, graphics::Texture* Ltexture)
	{
		animator->CreateAnimation(L"SkeletonWalkR", Rtexture, Vector2(0, 137), Vector2(140, 130), Vector2(0, 0), 0.4f, 6,6);
		animator->CreateAnimation(L"SkeletonWalkL", Ltexture, Vector2(970, 137), Vector2(140, 130), Vector2(0, 0), 0.4f, 6, 6);

		animator->CreateAnimation(L"SkeletonShoutR", Rtexture, Vector2(0, 0), Vector2(110, 130), Vector2(0, 0), 0.2f, 4);
		animator->CreateAnimation(L"SkeletonShoutL", Ltexture, Vector2(1000, 0), Vector2(110, 130), Vector2(0, 0), 0.2f, 4);
	
		animator->CreateAnimation(L"SkeletonIdleR", Rtexture, Vector2(560, 0), Vector2(90, 130), Vector2(0, 0), 0.1f, 1);
		animator->CreateAnimation(L"SkeletonIdleL", Ltexture, Vector2(450, 0), Vector2(90, 130), Vector2(0, 0), 0.1f, 1);

		animator->CreateAnimation(L"SkeletonAttackR", Rtexture, Vector2(117, 548), Vector2(123, 130), Vector2(0, 0), 0.2f, 8);
		animator->CreateAnimation(L"SkeletonAttackL", Ltexture, Vector2(874, 548), Vector2(123, 130), Vector2(0, 0), 0.2f, 8);

		animator->CreateAnimation(L"HurtL", Ltexture, Vector2(985, 880), Vector2(125, 130), Vector2::Zero, 0.05f, 3);
		animator->CreateAnimation(L"HurtR", Rtexture, Vector2(0, 880), Vector2(125, 130), Vector2::Zero, 0.05f, 3);

		animator->CreateAnimation(L"DeadL", Ltexture, Vector2(962, 1020), Vector2(148, 137), Vector2::Zero, 0.4f, 6);
		animator->CreateAnimation(L"DeadR", Rtexture, Vector2(0, 1020), Vector2(148, 137), Vector2::Zero, 0.4f, 6);


	
	}
	
}