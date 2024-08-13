#include "MEPlayScene.h"
#include "MEGameObject.h"
#include "MEPlayer.h"
#include "METransform.h"
#include "MESpriteRenderer.h"
#include "MEInput.h"
#include "METitleScene.h"
#include "MESceneManager.h"


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
	
		{
			bg = new Player();

			Transform* tr
				= bg->AddComponent<Transform>();
			
			tr->SetPos(Vector2(0,0));

			tr->SetName(L"TR");

			SpriteRenderer* sr
				= bg->AddComponent<SpriteRenderer>();

			sr->SetName(L"SR");
			sr->ImageLoad(L"C:\\Users\\SAMSUNG\\Desktop\\MyEngine\\myEngineforStudy\\Resources\\CloudOcean.png");

			AddGameObject(bg, eLayerType::BackGround);
		}
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
			SceneManager::LoadScreen(L"TitleScreen");
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
		Transform* tr = bg->GetComponent<Transform>();
		tr->SetPos(Vector2(0, 0));
	}
}
