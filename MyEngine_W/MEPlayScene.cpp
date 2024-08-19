#include "MEPlayScene.h"
#include "MEGameObject.h"
#include "MEPlayer.h"
#include "METransform.h"
#include "MESpriteRenderer.h"
#include "MEInput.h"
#include "METitleScene.h"
#include "MESceneManager.h"
#include "MEObject.h"
#include "METexture.h"
#include "MEResources.h"
#include "MEPlayerScript.h"
#include "MECamera.h"
#include "MERenderer.h"
#include "MEApplication.h"
#include "MEAnimator.h"

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
		
			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(0,0));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::mainCamera = cameraComp;

		//플레이어 생성
			mPlayer = object::Instantiate<Player>
				(enums::eLayerType::Player, Vector2(100, 406));

		//	SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			mPlayer->AddComponent<PlayerScript>();
			mPlayer->GetComponent<Transform>()->SetScale(Vector2(0.7f, 0.7f));
				
			graphics::Texture* megaman = Resources::Find<graphics::Texture>(L"MEGAMAN");
			Animator *animator = mPlayer->AddComponent<Animator>();
			

			//sr->SetTexture(megaman);
			animator->CreateAnimation(L"RightWalk", megaman, Vector2(0, 212.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.2f,8, 3);
			animator->CreateAnimation(L"Run", megaman, Vector2(0, 212.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.01f, 8, 3);
			animator->CreateAnimation(L"GetDown", megaman, Vector2(0, 0), Vector2(45.4f, 47.0f), Vector2(0, 0), 0.5f,6);
			animator->CreateAnimation(L"Jump", megaman, Vector2(0, 412), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.05f, 7);
			animator->CreateAnimation(L"Standing", megaman, Vector2(301.0f, 10.0f), Vector2(50.0f, 50.0f), Vector2(0, 0), 0.3f, 2,8);
			animator->CreateAnimation(L"StandAttack", megaman, Vector2(0, 112), Vector2(50.0f, 50.0f), Vector2::Zero, 0.1f, 3);
			animator->CreateAnimation(L"RunningAttack", megaman, Vector2(250, 262), Vector2(50.0f, 50.0f), Vector2::Zero,0.1f, 3,8);
			
			GameObject* Bullet = object::Instantiate<GameObject>(enums::eLayerType::Paritcle);
			graphics::Texture* bulletTexture = Resources::Find<graphics::Texture>(L"BULLETEFFECT");
			Animator* particleAnimator = Bullet->AddComponent<Animator>();

			animator->CreateAnimation(L"BulletEffect", bulletTexture, Vector2(0,0), Vector2(100, 20), Vector2::Zero,0.1f, 8);
			

			//mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100, 800));

		

		//맵생성
	
			GameObject* bg = object::Instantiate<GameObject>
				(enums::eLayerType::BackGround, Vector2(0,200.0f));

			SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
			bgSr->SetSize(Vector2(1.3f, 1.3f));


			graphics::Texture* map = Resources::Find<graphics::Texture>(L"STAGE1_1");
			bgSr->SetTexture(map);

			animator->PlayAnimation(L"Standing", true);
		
	//
	//{//기타 오브젝트 생성
	//	GameObject* flower = object::Instantiate<GameObject>
	//		(enums::eLayerType::Items, Vector2(300, 215));
	//
	//	SpriteRenderer* flowerSr = flower->AddComponent<SpriteRenderer>();
	//	flowerSr->SetSize(Vector2(0.03f, 0.03f));
	//
	//	graphics::Texture* flowerTexture = Resources::Find<graphics::Texture>(L"FLOWER");
	//	flowerSr->SetTexture(flowerTexture);
	//
	//	GameObject* qbox = object::Instantiate<GameObject>
	//		(enums::eLayerType::Items, Vector2(500, 150));
	//
	//	SpriteRenderer* qboxSr = qbox->AddComponent<SpriteRenderer>();
	//	qboxSr->SetSize(Vector2(0.04f, 0.04f));
	//
	//	graphics::Texture* qboxTexture = Resources::Find<graphics::Texture>(L"QUESTIONBOX");
	//	qboxSr->SetTexture(qboxTexture);
	//
	//	GameObject* qbox2 = object::Instantiate<GameObject>
	//		(enums::eLayerType::Items, Vector2(200, 150));
	//
	//	SpriteRenderer* qbox2Sr = qbox2->AddComponent<SpriteRenderer>();
	//	qbox2Sr->SetSize(Vector2(0.04f, 0.04f));
	//
	//	graphics::Texture* qbox2Texture = Resources::Find<graphics::Texture>(L"QUESTIONBOX");
	//	qbox2Sr->SetTexture(qbox2Texture);
	//}
	//
		
		

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

		Transform* tr = mPlayer->GetComponent<Transform>();
		Vector2 playerPos = tr->GetPosition();

		if (playerPos.x > application.GetWidth() 
			|| playerPos.x < 0)
		{
			SceneManager::LoadScene(L"GameOverScene");
		}


		if (playerPos.y < 0
			|| playerPos.y > application.GetHeight())
		{
			SceneManager::LoadScene(L"GameOverScene");
		}
	}

	void PlayScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
		wchar_t str[50] = L"PlayScene";
		TextOut(mHdc, 0, 0, str, 9);
	}

	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		mPlayer = object::Instantiate<Player>
			(enums::eLayerType::Player, Vector2(100, 407));



		GameObject* bg = object::Instantiate<GameObject>
			(enums::eLayerType::BackGround, Vector2(0, 200.0f));

		SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
		bgSr->SetSize(Vector2(1.3f, 1.3f));


		graphics::Texture* map = Resources::Find<graphics::Texture>(L"STAGE1_1");
		bgSr->SetTexture(map);
	}
}