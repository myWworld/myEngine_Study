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

extern ME::Application application;

namespace ME
{

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


		titleBg = object::Instantiate<GameObject>(enums::eLayerType::BackGround, Vector2(250, 60));

		SpriteRenderer* sr = titleBg->AddComponent<SpriteRenderer>();

		Transform* tr = titleBg->GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));

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
		wchar_t str[50] = L"�����Ϸ��� Enter�� ��������.";
		UINT len = wcslen(str);
		TextOut(mHdc, 380, 350, str, len);
	}

	void TitleScene::OnEnter()
	{
		Transform* tr = titleBg->GetComponent<Transform>();
		tr->SetPosition(Vector2(250, 60));

		renderer::mainCamera = mCameraComp;
		Scene::OnEnter();

	}

	void TitleScene::OnExit()
	{
		Scene::OnExit();

	}

}