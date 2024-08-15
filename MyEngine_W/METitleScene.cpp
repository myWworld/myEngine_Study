#include "METitleScene.h"
#include "MEInput.h"
#include "MESceneManager.h"
#include "MEPlayScene.h"
#include "MEObject.h"
#include "MECamera.h"
#include "MERenderer.h"
#include "MESpriteRenderer.h"
#include "METexture.h"
#include "MEResource.h"
#include "MEResources.h"

ME::TitleScene::TitleScene()
{
}

ME::TitleScene::~TitleScene()
{
}

void ME::TitleScene::Initialize()
{
	GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(504, 216));

	Camera* cameraComp = camera->AddComponent<Camera>();
	renderer::mainCamera = cameraComp;

	GameObject* titleBg = object::Instantiate<GameObject>(enums::eLayerType::BackGround, Vector2(280, 100));

	SpriteRenderer* sr = titleBg->AddComponent<SpriteRenderer>();
	sr->SetSize(Vector2(0.2f, 0.2f));
	
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

 	if (Input::GetKeyDown(eKeyCode::Space))
	{
 		SceneManager::LoadScene(L"PlayScene");
	}

}

void ME::TitleScene::Render(HDC mHdc)
{	
	Scene::Render(mHdc);
	wchar_t str[50] = L"시작하려면 SPACE를 누르세요.";
	UINT len = wcslen(str);
	TextOut(mHdc, 380, 350, str, len);
}
