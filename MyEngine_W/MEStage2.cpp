#include "MEStage2.h"
#include "ContentAndScript.h"

#include "MEGameObject.h"

#include "MEInput.h"
#include "METitleScene.h"
#include "MEObject.h"
#include "MEResources.h"
#include "METime.h"
#include "MEFmod.h"
#include "MEAudioClip.h"
#include "MEAudioSource.h"
#include "MEAudioListener.h"

#include "MESceneManager.h"
#include "METransform.h"
#include "MESpriteRenderer.h"
#include "MEBoxCollider2D.h"
#include "MERigidbody.h"

#include "MERenderer.h"
#include "MEApplication.h"

#include "MEUIManager.h"
#include "MEUIHUD.h"
#include "MEUIButton.h"

#include "METileMapRenderer.h"

#include "MECollisionManager.h"


extern ME::Application application;

namespace ME
{


	ME::Stage2::Stage2()
	{
	}

	ME::Stage2::~Stage2()
	{
	}

	void ME::Stage2::Initialize()
	{
		{	
			Vector2 resolution = Vector2(application.GetWidth(), application.GetHeight());

			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, resolution / 2.0f);
			mCameraComp = camera->AddComponent<Camera>();

			renderer::mainCamera = mCameraComp;

		}

		{
			GameObject* background = object::Instantiate<GameObject>(enums::eLayerType::BackGround,Vector2(0,0));
			SpriteRenderer* backgroundSr = background->AddComponent<SpriteRenderer>();

			graphics::Texture* backgroundTex = Resources::Find<graphics::Texture>(L"STAGE2");

			backgroundSr->SetTexture(backgroundTex);

		}
		{
			Floor* floor = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(0, 210));
			CreateFloor(floor, 2.56);

			Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(289, 210));
			CreateFloor(floor1, 0.48,0.04);
			Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(337, 147));
			CreateFloor(floor2, 0.48, 0.04);
			Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(385, 210));
			CreateFloor(floor3, 0.48, 0.04);

			Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(1430, 210));
			CreateFloor(floor4, 10);
			Floor* floor8 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(2560, 210));
			CreateFloor(floor8, 3.04);
		}

		Scene::Initialize();
	}

	void ME::Stage2::Update()
	{
		Scene::Update();
	}

	void ME::Stage2::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void ME::Stage2::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
	}

	void ME::Stage2::OnEnter()
	{
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Particle, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Particle, enums::eLayerType::Player, true);


		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Stair, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Chimney, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Block, true);

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Stair, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Chimney, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Block, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Flag, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Items, enums::eLayerType::Stair, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Items, enums::eLayerType::Chimney, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Items, enums::eLayerType::Block, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Items, enums::eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Items, enums::eLayerType::Floor, true);



		mPlayer = object::Instantiate<Player>
			(enums::eLayerType::Player, Vector2(55, 215));


		renderer::mainCamera = mCameraComp;
		mCameraComp->SetTarget(mPlayer);

		playerInitialize();
		PlayerScript::ReSetScore(0.0f);
		mPlayTime = 0.0f;

		UIManager::Push(enums::eUIType::HpBar);

		Scene::OnEnter();
	}

	void ME::Stage2::OnExit()
	{
		UIManager::Pop(enums::eUIType::HpBar);
		Scene::OnExit();
	}

	void ME::Stage2::CreatePlayerAnimation(Animator* animator, graphics::Texture* Rtexture, graphics::Texture* Ltexture)
	{
		animator->CreateAnimation(L"RightWalkR", Rtexture, Vector2(0, 212.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.1f, 8, 3);
		animator->CreateAnimation(L"LeftWalkL", Ltexture, Vector2(356, 212.0f), Vector2(50, 50), Vector2(0, 0), 0.1f, 8, 3);

		animator->CreateAnimation(L"RunR", Rtexture, Vector2(0, 212.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.07f, 8, 3);
		animator->CreateAnimation(L"RunL", Ltexture, Vector2(356, 212), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.07f, 8, 3);

		animator->CreateAnimation(L"JumpR", Rtexture, Vector2(0, 412), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.1f, 7);
		animator->CreateAnimation(L"JumpL", Ltexture, Vector2(356, 412), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.1f, 7);

		animator->CreateAnimation(L"StandingR", Rtexture, Vector2(301.0f, 10.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.3f, 2, 8);
		animator->CreateAnimation(L"StandingL", Ltexture, Vector2(55.0f, 10.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.3f, 2, 8);

		animator->CreateAnimation(L"StandAttackR", Rtexture, Vector2(0, 112), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3);
		animator->CreateAnimation(L"RunningAttackR", Rtexture, Vector2(245, 262), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3, 8);

		animator->CreateAnimation(L"StandAttackL", Ltexture, Vector2(357, 112), Vector2(49.0f, 50.0f), Vector2::Zero, 0.1f, 3);
		animator->CreateAnimation(L"RunningAttackL", Ltexture, Vector2(100, 262), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3, 8);

		animator->CreateAnimation(L"HurtL", Ltexture, Vector2(54, 162), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 2);
		animator->CreateAnimation(L"HurtR", Rtexture, Vector2(251, 162), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 2);

		animator->CreateAnimation(L"ClearL", Rtexture, Vector2(152, 582), Vector2(48.0f, 50.0f), Vector2::Zero, 0.45f, 4);
	}

	void ME::Stage2::CreateMushRoomAnimation(Animator* animator, graphics::Texture* Rtexture, graphics::Texture* Ltexture)
	{
	}

	void ME::Stage2::CreateSkeletonAnimation(Animator* animator, graphics::Texture* Rtexture, graphics::Texture* Ltexture)
	{
	}

	void ME::Stage2::CreateMushRoom(GameObject* mushroom)
	{
	}

	void ME::Stage2::CreateSkeleton(GameObject* skeleton)
	{
	}

	void ME::Stage2::CreateCannon()
	{
	}

	void ME::Stage2::CreateQbox(GameObject* qbox)
	{
		BoxCollider2D* qboxCol = qbox->AddComponent<BoxCollider2D>();

		qbox->AddComponent<QboxScript>();


		qboxCol->SetOffset(Vector2(-100, -100));
		qboxCol->SetSize(Vector2(0.2f, 0.2f));

		Animator* qboxAnimator = qbox->AddComponent<Animator>();

		qbox->GetComponent<Transform>()->SetScale(Vector2(0.1f, 0.1f));

		graphics::Texture* qboxTex = Resources::Find<graphics::Texture>(L"QBOX");
		graphics::Texture* usedQboxTex = Resources::Find<graphics::Texture>(L"USEDQBOX");

		qboxAnimator->CreateAnimation(L"IdleR", qboxTex, Vector2(0, 0), Vector2(200, 200), Vector2::Zero
			, 0.2f, 4);
		qboxAnimator->CreateAnimation(L"UsedR", usedQboxTex, Vector2(0, 0), Vector2(240, 242), Vector2(17, 17)
			, 0.2f, 1);

		qboxAnimator->PlayAnimation(L"IdleR", true);
	}

	void Stage2::CreateFloor(GameObject* floor, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
		floor->AddComponent<FloorScript>();
		floorCol->SetName(L"Floor");

		floorCol->SetSize(Vector2(xSize, ySize));
		floorCol->SetOffset(Vector2(xOffset, yOffset));
	}
	void Stage2::CreateLastDoor(GameObject* lastdoor, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* lastDoorCol = lastdoor->AddComponent<BoxCollider2D>();
		lastdoor->AddComponent<LastDoorScript>();
		lastDoorCol->SetName(L"LastDoor");

		lastDoorCol->SetSize(Vector2(xSize, ySize));
		lastDoorCol->SetOffset(Vector2(xOffset, yOffset));
	}
	void Stage2::CreateChimney(GameObject* chimney, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* chimneyCol = chimney->AddComponent<BoxCollider2D>();
		chimney->AddComponent<ChimneyScript>();
		chimneyCol->SetName(L"Chimney");

		chimneyCol->SetSize(Vector2(xSize, ySize));
		chimneyCol->SetOffset(Vector2(xOffset, yOffset));
	}
	void Stage2::CreateStair(Vector2 startPos, int maxSteps, int height, char direction)
	{

		int stairSize = 16;
		float stairSizeForCol = stairSize / 100.0f;

		if (direction == 'R')
		{
			for (int i = 0; i < height; i++)
			{
				Block* stair = object::Instantiate<Block>(enums::eLayerType::Block
					, Vector2(startPos.x + stairSize * i, startPos.y - stairSize * i));

				BoxCollider2D* stairCol = stair->AddComponent<BoxCollider2D>();
				stair->AddComponent<BlockScript>();
				stairCol->SetName(L"Stair");

				stairCol->SetSize(Vector2(stairSizeForCol * (maxSteps - i), stairSizeForCol));

			}
		}
		else if (direction == 'L')
		{
			for (int i = 0; i < height; i++)
			{
				Block* stair = object::Instantiate<Block>(enums::eLayerType::Stair
					, Vector2(startPos.x, startPos.y - stairSize * i));

				BoxCollider2D* stairCol = stair->AddComponent<BoxCollider2D>();
				stair->AddComponent<BlockScript>();
				stairCol->SetName(L"Stair");

				stairCol->SetSize(Vector2(stairSizeForCol * (maxSteps - i), stairSizeForCol));

			}
		}



	}
	void Stage2::CreateFlag(GameObject* flag, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* flagCol = flag->AddComponent<BoxCollider2D>();
		flag->AddComponent<FlagScript>();
		flagCol->SetName(L"Flag");

		flagCol->SetSize(Vector2(xSize, ySize));
		flagCol->SetOffset(Vector2(xOffset, yOffset));
	}
	void Stage2::CreateBlock(GameObject* block, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* BlockCol = block->AddComponent<BoxCollider2D>();
		block->AddComponent<BlockScript>();
		BlockCol->SetName(L"Block");

		BlockCol->SetSize(Vector2(xSize, ySize));
		BlockCol->SetOffset(Vector2(xOffset, yOffset));
	}

	void ME::Stage2::playerInitialize()
	{
		PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();

		playerScript->SetEffect(mEffect);

		PlayerScript::ReSetHp(100.0f);


		mPlayer->GetComponent<Transform>()->SetScale(Vector2(0.5f, 0.5f));
		mPlayer->GetComponent<Transform>()->SetName(L"Player");

		mPlayer->AddComponent <Rigidbody>();

		mPlayer->AddComponent<AudioListener>();
		mPlayer->AddComponent<AudioSource>();
		;
		Rigidbody* playerRb = mPlayer->GetComponent<Rigidbody>();
		playerRb->SetMass(1.0f);

		BoxCollider2D* playerBoxCollider = mPlayer->AddComponent<BoxCollider2D>();
		playerBoxCollider->SetName(L"Player");

		playerBoxCollider->SetOffset(Vector2(-17, -20));
		playerBoxCollider->SetSize(Vector2(0.13f, 0.18f));

		//object::DontDestroyOnLoad(mPlayer);


		graphics::Texture* megamanRightTex = Resources::Find<graphics::Texture>(L"MEGAMANR");
		graphics::Texture* megamanLeftTex = Resources::Find<graphics::Texture>(L"MEGAMANL");

		Animator* animator = mPlayer->AddComponent<Animator>();


		CreatePlayerAnimation(animator, megamanRightTex, megamanLeftTex);
		animator->PlayAnimation(L"StandingR", true);


		animator->GetCompleteEvent(L"StandAttackL") = std::bind(&PlayerScript::MakeBullet, playerScript, false);
		animator->GetCompleteEvent(L"StandAttackR") = std::bind(&PlayerScript::MakeBullet, playerScript, false);
	}

}