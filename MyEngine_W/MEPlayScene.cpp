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
		
			GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(504,216));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::mainCamera = cameraComp;

		{ //플레이어 생성
			mPlayer = object::Instantiate<Player>
				(enums::eLayerType::Player, Vector2(150, 215));

			SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
			mPlayer->AddComponent<PlayerScript>();
			sr->SetSize(Vector2(0.02f, 0.02f));

			graphics::Texture* mario = Resources::Find<graphics::Texture>(L"MARIO");
			sr->SetTexture(mario);

		}

		{//맵생성
	
			GameObject* bg = object::Instantiate<GameObject>
				(enums::eLayerType::BackGround);

			SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();

			graphics::Texture* map = Resources::Find<graphics::Texture>(L"MAP");
			bgSr->SetTexture(map);
		}

		{//기타 오브젝트 생성
			GameObject* flower = object::Instantiate<GameObject>
				(enums::eLayerType::Items, Vector2(300, 165));

			SpriteRenderer* flowerSr = flower->AddComponent<SpriteRenderer>();
			flowerSr->SetSize(Vector2(0.03f, 0.03f));

			graphics::Texture* flowerTexture = Resources::Find<graphics::Texture>(L"FLOWER");
			flowerSr->SetTexture(flowerTexture);

			GameObject* qbox = object::Instantiate<GameObject>
				(enums::eLayerType::Items, Vector2(500, 100));

			SpriteRenderer* qboxSr = qbox->AddComponent<SpriteRenderer>();
			qboxSr->SetSize(Vector2(0.04f, 0.04f));

			graphics::Texture* qboxTexture = Resources::Find<graphics::Texture>(L"QUESTIONBOX");
			qboxSr->SetTexture(qboxTexture);

			GameObject* qbox2 = object::Instantiate<GameObject>
				(enums::eLayerType::Items, Vector2(200, 100));

			SpriteRenderer* qbox2Sr = qbox2->AddComponent<SpriteRenderer>();
			qbox2Sr->SetSize(Vector2(0.04f, 0.04f));

			graphics::Texture* qbox2Texture = Resources::Find<graphics::Texture>(L"QUESTIONBOX");
			qbox2Sr->SetTexture(qbox2Texture);
		}

		
		

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
			(enums::eLayerType::Player, Vector2(150, 215));

		SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
		mPlayer->AddComponent<PlayerScript>();
		sr->SetSize(Vector2(0.02f, 0.02f));

		graphics::Texture* mario = Resources::Find<graphics::Texture>(L"MARIO");
		sr->SetTexture(mario);
	}
}