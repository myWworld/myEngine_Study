#include "MEStage1.h"
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

#include "ContentAndScript.h"


#include "MECollisionManager.h"


extern ME::Application application;



namespace ME
{	
	

	Stage1::Stage1()
		:mPlayTime(0.0f)
	{
	}

	Stage1::~Stage1()
	{
	}

	void Stage1::Initialize()
	{
		
		//만약 타일맵 만들면 _wfopen_s함수로 불러온다음에 찍어내면됨 타일 렌더러 load함수에 있는거 가져다 쓰면됨.

		Vector2 resolution = Vector2(application.GetWidth(), application.GetHeight());

		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(resolution.x,resolution.y ));
		mCameraComp = camera->AddComponent<Camera>();

		renderer::mainCamera = mCameraComp;
		
		{
			GameObject* bg = object::Instantiate<GameObject>
				(enums::eLayerType::BackGround, Vector2(0, 0));

			SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();



			graphics::Texture* map = Resources::Find<graphics::Texture>(L"STAGE1_1");
			bgSr->SetTexture(map);

		}

		{//qbox
			GameObject* qbox1 = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(200, 240));
			CreateQbox(qbox1);

			GameObject* qbox2 = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(620, 240));
			CreateQbox(qbox2);
		}

		{
			Floor* floor = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(0, 210));
			CreateFloor(floor, 11);
			Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(1142, 210));
			CreateFloor(floor1, 2.3);
			Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(1430, 210));
			CreateFloor(floor2, 10);
			Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor, Vector2(2490, 210));
			CreateFloor(floor3, 10);
		}//floor

		{
			Chimney* chimney = object::Instantiate<Chimney>(enums::eLayerType::Chimney, Vector2(450, 175));
			CreateChimney(chimney,0.30,0.35);

			Chimney* chimney1 = object::Instantiate<Chimney>(enums::eLayerType::Chimney, Vector2(610, 160));
			CreateChimney(chimney1, 0.30, 0.5);

			Chimney* chimney2 = object::Instantiate<Chimney>(enums::eLayerType::Chimney, Vector2(738, 145));
			CreateChimney(chimney2, 0.30, 0.65);
		
			Chimney* chimney3 = object::Instantiate<Chimney>(enums::eLayerType::Chimney, Vector2(915, 145));
			CreateChimney(chimney3, 0.30, 0.65);

			Chimney* chimney4 = object::Instantiate<Chimney>(enums::eLayerType::Chimney, Vector2(2610, 175));
			CreateChimney(chimney4, 0.30, 0.35);

			Chimney* chimney5 = object::Instantiate<Chimney>(enums::eLayerType::Chimney, Vector2(2867, 175));
			CreateChimney(chimney5, 0.30, 0.35);


		}//chimney

		{
			CreateStair(Vector2(2146, 195), 4, 4, 'R');
			CreateStair(Vector2(2242, 195), 4, 4, 'L');

			CreateStair(Vector2(2369, 195), 5, 4, 'R');
			CreateStair(Vector2(2482, 195), 4, 4, 'L');

			CreateStair(Vector2(2897, 195), 9, 8, 'R');
		}//stair

		{
			Flag* flag = object::Instantiate<Flag>(enums::eLayerType::Flag, Vector2(3176, 50));
			CreateFlag(flag, 0.01, 1.45);
		}//flag
		
		{
			Block* block = object::Instantiate<Block>(enums::eLayerType::Block, Vector2(3169,194));
			CreateBlock(block, 0.16, 0.16);

		}//blocks

		{
			LastDoor* lastdoor = object::Instantiate<LastDoor>(enums::eLayerType::Block,Vector2(3280,178));
			CreateLastDoor(lastdoor, 0.16, 0.32);
		}//LastDoor Just For Using Collider 

		{
	//		GameObject* mushroom = object::Instantiate<MushRoom>(enums::eLayerType::Monster, Vector2(400, 425));
	//		CreateMushRoom(mushroom);
	//		
	//		GameObject* mushroom1 = object::Instantiate<MushRoom>(enums::eLayerType::Monster, Vector2(700, 425));
	//		CreateMushRoom(mushroom1);
		
		}//mushroom

		{
	//		GameObject* skeleton = object::Instantiate<Skeleton>(enums::eLayerType::Monster
	//			, Vector2(600, 406));
	//
	//		CreateSkeleton(skeleton);
	//		
	//
		}//skeleton

			
			
		

		Scene::Initialize();
	}

	

	void Stage1::Update()
	{
		Scene::Update();
		mPlayTime += Time::DeltaTime();

		if (mPlayTime > 5.0f)
		{
			CreateCannon();
			mPlayTime = 0;
		}

	}

	void Stage1::LateUpdate()
	{
		Scene::LateUpdate();
	}


	void Stage1::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
	}

	void Stage1::OnEnter()
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
			(enums::eLayerType::Player, Vector2(100, 210));


		renderer::mainCamera = mCameraComp;
		mCameraComp->SetTarget(mPlayer);

		playerInitialize();
		PlayerScript::ReSetScore(0.0f);
		mPlayTime = 0.0f;

		UIManager::Push(enums::eUIType::HpBar);

		Scene::OnEnter();

	}
	void Stage1::OnExit()
	{
		UIManager::Pop(enums::eUIType::HpBar);
		Scene::OnExit();
	}

	void Stage1::playerInitialize()
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
		playerBoxCollider->SetSize(Vector2(0.13f, 0.20f));

		//	object::DontDestroyOnLoad(mPlayer);
		

		graphics::Texture* megamanRightTex = Resources::Find<graphics::Texture>(L"MEGAMANR");
		graphics::Texture* megamanLeftTex = Resources::Find<graphics::Texture>(L"MEGAMANL");

		Animator* animator = mPlayer->AddComponent<Animator>();


		CreatePlayerAnimation(animator, megamanRightTex, megamanLeftTex);
		animator->PlayAnimation(L"StandingR", true);


		animator->GetCompleteEvent(L"StandAttackL") = std::bind(&PlayerScript::MakeBullet, playerScript,false);
		animator->GetCompleteEvent(L"StandAttackR") = std::bind(&PlayerScript::MakeBullet, playerScript,false);

		//				animator->GetStartEvent(L"RunningAttackR") = std::bind(&PlayerScript::MakeBullet, playerScript);

	}

	void Stage1::CreatePlayerAnimation(Animator* animator
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
		animator->CreateAnimation(L"RunningAttackR", Rtexture, Vector2(245, 262), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3, 8);

		animator->CreateAnimation(L"StandAttackL", Ltexture, Vector2(357, 112), Vector2(49.0f, 50.0f), Vector2::Zero, 0.1f, 3);
		animator->CreateAnimation(L"RunningAttackL", Ltexture, Vector2(100, 262), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3, 8);

		animator->CreateAnimation(L"HurtL", Ltexture, Vector2(54, 162), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 2);
		animator->CreateAnimation(L"HurtR", Rtexture, Vector2(251, 162), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 2);

		animator->CreateAnimation(L"ClearL", Rtexture, Vector2(152, 582), Vector2(48.0f, 50.0f), Vector2::Zero, 0.45f, 4);
	}

	void Stage1::CreateMushRoomAnimation(Animator* animator
		, graphics::Texture* Rtexture
		, graphics::Texture* Ltexture)
	{
		animator->CreateAnimation(L"MushRoomLeftWalkR", Ltexture, Vector2(0, 126.0f), Vector2(133.5f, 137), Vector2::Zero, 0.5f, 5);
		animator->CreateAnimation(L"MushRoomRightWalkL", Rtexture, Vector2(700, 126.0f), Vector2(133.5f, 137), Vector2::Zero, 0.5f, 5);
		animator->CreateAnimation(L"IdleL", Ltexture, Vector2(0, 0), Vector2(130, 130), Vector2::Zero, 0.2f, 1);

		animator->CreateAnimation(L"HurtL", Ltexture, Vector2(0, 395), Vector2(130, 150), Vector2::Zero, 0.02f, 1);
		animator->CreateAnimation(L"HurtR", Rtexture, Vector2(703, 395), Vector2(130, 150), Vector2::Zero, 0.02f, 1);

		animator->CreateAnimation(L"DeadR", Ltexture, Vector2(0, 1056), Vector2(202, 140), Vector2::Zero, 0.2f, 4, 2);
	}

	void Stage1::CreateSkeletonAnimation(Animator* animator
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

		animator->CreateAnimation(L"DeadL", Ltexture, Vector2(962, 1020), Vector2(148, 137), Vector2::Zero, 0.2f, 6);
		animator->CreateAnimation(L"DeadR", Rtexture, Vector2(0, 1020), Vector2(148, 137), Vector2::Zero, 0.2f, 6);


	
	}


	void Stage1::CreateCannon()
	{
		Transform* playerTr = mPlayer->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();


		Cannon* cannon = object::Instantiate<Cannon>(enums::eLayerType::Monster, Vector2(playerPos.x + application.GetWidth()/2.0f, 206));

		Rigidbody* cannonRb = cannon->AddComponent<Rigidbody>();
		cannonRb->SetNeedGravity(false);

		cannon->GetComponent<Transform>()->SetScale(Vector2(0.6f, 0.6f));

		BoxCollider2D* cannonCol = cannon->AddComponent<BoxCollider2D>();
		CannonScript* cannonScript = cannon->AddComponent<CannonScript>();
		Animator* cannonAnimator = cannon->AddComponent<Animator>();

		cannonCol->SetSize(Vector2(0.4f, 0.2f));
		cannonCol->SetOffset(Vector2(-30, -18));
		cannonCol->SetName(L"Cannon");

		graphics::Texture* cannonTex = Resources::Find<graphics::Texture>(L"CANNON");
		
		cannonAnimator->CreateAnimation(L"CannonL", cannonTex, Vector2(0, 0), Vector2(60, 40), Vector2::Zero, 0.1f, 1);
	
		cannonAnimator->PlayAnimation(L"CannonL");
	
	}
	void Stage1::CreateMushRoom(GameObject* mushroom)
	{
		MushRoomScript* mushroomScript = mushroom->AddComponent<MushRoomScript>();
		Animator* mushroomAnimator = mushroom->AddComponent<Animator>();

		BoxCollider2D* mushroomBoxCollider = mushroom->AddComponent<BoxCollider2D>();
		mushroom->AddComponent<Rigidbody>();
		mushroomBoxCollider->SetName(L"Mushroom");

		mushroomBoxCollider->SetOffset(Vector2(-65, -65));
		mushroomBoxCollider->SetSize(Vector2(0.5f, 0.5f));


		mushroom->GetComponent<Transform>()->SetScale(Vector2(0.4f, 0.4f));
		graphics::Texture* mushroomLeftTex = Resources::Find<graphics::Texture>(L"MUSHROOML");
		graphics::Texture* mushroomRightTex = Resources::Find<graphics::Texture>(L"MUSHROOMR");

		CreateMushRoomAnimation(mushroomAnimator, mushroomRightTex, mushroomLeftTex);

		mushroomAnimator->GetCompleteEvent(L"DeadR") = std::bind(&MushRoomScript::Respawn, mushroomScript);

		mushroomAnimator->PlayAnimation(L"IdleL", false);
	}
	void Stage1::CreateSkeleton(GameObject* skeleton)
	{
		BoxCollider2D* skeletonCollider = skeleton->AddComponent<BoxCollider2D>();
		skeleton->AddComponent<Rigidbody>();

		skeletonCollider->SetName(L"Skeleton");

		skeletonCollider->SetOffset(Vector2(-34, -40));
		skeletonCollider->SetSize(Vector2(0.2f, 0.5f));


		SkeletonScript* skeletonScript = skeleton->AddComponent<SkeletonScript>();
		Animator* skeletonAnimator = skeleton->AddComponent<Animator>();
		skeleton->GetComponent<Transform>()->SetScale(Vector2(0.6f, 0.6f));

		graphics::Texture* skeletonLeftTex = Resources::Find<graphics::Texture>(L"SKELETONL");
		graphics::Texture* skeletonRightTex = Resources::Find<graphics::Texture>(L"SKELETONR");

		CreateSkeletonAnimation(skeletonAnimator, skeletonRightTex, skeletonLeftTex);


		skeletonAnimator->GetCompleteEvent(L"DeadL") = std::bind(&SkeletonScript::Respawn, skeletonScript);
		skeletonAnimator->GetCompleteEvent(L"DeadR") = std::bind(&SkeletonScript::Respawn, skeletonScript);


		skeletonAnimator->PlayAnimation(L"SkeletonIdleR", false);
	}

	void Stage1::CreateQbox(GameObject* qbox)
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
	void Stage1::CreateFloor(GameObject* floor, float xSize, float ySize, float xOffset,float yOffset)
	{
		BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
		floor->AddComponent<FloorScript>();
		floorCol->SetName(L"Floor");

		floorCol->SetSize(Vector2(xSize, ySize));
		floorCol->SetOffset(Vector2(xOffset, yOffset));
	}

	void Stage1::CreateLastDoor(GameObject* lastdoor, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* lastDoorCol = lastdoor->AddComponent<BoxCollider2D>();
		lastdoor->AddComponent<LastDoorScript>();
		lastDoorCol->SetName(L"LastDoor");

		lastDoorCol->SetSize(Vector2(xSize, ySize));
		lastDoorCol->SetOffset(Vector2(xOffset, yOffset));
	}


	void Stage1::CreateChimney(GameObject* chimney, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* chimneyCol = chimney->AddComponent<BoxCollider2D>();
		chimney->AddComponent<ChimneyScript>();
		chimneyCol->SetName(L"Chimney");

		chimneyCol->SetSize(Vector2(xSize, ySize));
		chimneyCol->SetOffset(Vector2(xOffset, yOffset));
	}
	void Stage1::CreateStair(Vector2 startPos, int maxSteps, int height, char direction)
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
	void Stage1::CreateFlag(GameObject* flag, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* flagCol = flag->AddComponent<BoxCollider2D>();
		flag->AddComponent<FlagScript>();
		flagCol->SetName(L"Flag");
		
		flagCol->SetSize(Vector2(xSize, ySize));
		flagCol->SetOffset(Vector2(xOffset, yOffset));
	}
	void Stage1::CreateBlock(GameObject* block, float xSize, float ySize, float xOffset, float yOffset)
	{
		BoxCollider2D* BlockCol = block->AddComponent<BoxCollider2D>();
		block->AddComponent<BlockScript>();
		BlockCol->SetName(L"Block");

		BlockCol->SetSize(Vector2(xSize, ySize));
		BlockCol->SetOffset(Vector2(xOffset, yOffset));
	}



}