#include "MEGameOverScene.h"
#include "MEObject.h"
#include "MECamera.h"
#include "MERenderer.h"
#include "MESpriteRenderer.h"
#include "METexture.h"
#include "MEResources.h"
#include "MEInput.h"


namespace ME
{
	GameOverScene::GameOverScene()
	{
	}
	GameOverScene::~GameOverScene()
	{
	}
	void GameOverScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(504, 216));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		
		GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::BackGround, Vector2 (280,-10));
		
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		sr->SetSize(Vector2(0.3, 0.3));
		
		graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"GAMEOVER");
		sr->SetTexture(bgTexture);

		Scene::Initialize();

	}
	void GameOverScene::Update()
	{
		Scene::Update();
	}
	void GameOverScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKey(eKeyCode::Space))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void GameOverScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
		wchar_t str[50] = L"처음으로 돌아가려면 SPACE를 누르시오.";
		UINT len = wcslen(str);

		TextOut(mHdc, 340, 300, str, len);
	}
}