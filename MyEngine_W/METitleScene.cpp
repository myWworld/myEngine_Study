#include "METitleScene.h"
#include "MEInput.h"
#include "MESceneManager.h"
#include "MEPlayScene.h"
#include "MEObject.h"
#include "MERenderer.h"
#include "MESpriteRenderer.h"
#include "METexture.h"
#include "MEResource.h"
#include "MEResources.h"
#include "METransform.h"
#include "MEApplication.h"
#include "MEUIManager.h"

extern ME::Application application;

namespace ME
{
	GameObject* TitleScene::redTriangle = nullptr;

	ME::TitleScene::TitleScene()
	{
	}

	ME::TitleScene::~TitleScene()
	{
	}

	void ME::TitleScene::Initialize()
	{
		Vector2 resolution = Vector2(application.GetWidth(), application.GetHeight());

		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, resolution / 2.0f);
		mCameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = mCameraComp;

		redTriangle = object::Instantiate<GameObject>(enums::eLayerType::BackGround,Vector2(375, 345));
		SpriteRenderer* redTriangleSr = redTriangle->AddComponent<SpriteRenderer>();
		graphics::Texture* redTriangleTex = Resources::Find<graphics::Texture>(L"REDTRIANGLE");
		
		redTriangleSr->SetTexture(redTriangleTex);


		redTriangle->SetNoRender(false);

		titleBg = object::Instantiate<GameObject>(enums::eLayerType::BackGround);

		SpriteRenderer* sr = titleBg->AddComponent<SpriteRenderer>();

		Transform* tr = titleBg->GetComponent<Transform>();
		tr->SetScale(Vector2(0.5f, 0.5f));
		tr->SetPosition(Vector2(0, 300));

		graphics::Texture* titleTexture = Resources::Find<graphics::Texture>(L"TITLE");
		sr->SetTexture(titleTexture);

		Scene::Initialize();


	}

	void ME::TitleScene::Update()
	{
		Scene::Update();
	}

	void ME::TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::Enter))
		{
			SceneManager::LoadScene(L"PlayScene");
		}

	}

	void ME::TitleScene::Render(HDC mHdc)
	{
 		Scene::Render(mHdc);
	
	}

	void TitleScene::OnEnter()
	{
		Transform* tr = titleBg->GetComponent<Transform>();
		tr->SetPosition(Vector2(250, 60));

		renderer::mainCamera = mCameraComp;

		UIManager::Push(enums::eUIType::Button);
		
		Scene::OnEnter();

	}

	void TitleScene::OnExit()
	{
		UIManager::Pop(enums::eUIType::Button);

		Scene::OnExit();

	}

}