#include "METitleScene.h"
#include "MEInput.h"
#include "MESceneManager.h"
#include "MEPlayScene.h"


ME::TitleScene::TitleScene()
{
}

ME::TitleScene::~TitleScene()
{
}

void ME::TitleScene::Initialize()
{
	Scene::Initialize();
}

void ME::TitleScene::Update()
{
	Scene::Update();
}

void ME::TitleScene::LateUpdate()
{
	Scene::LateUpdate();

	if (Input::GetKeyDown(eKeyCode::N))
	{
		SceneManager::LoadScreen(L"PlayScene");
	}

}

void ME::TitleScene::Render(HDC mHdc)
{	
	Scene::Render(mHdc);
	wchar_t str[50] = L"TitleScene";
	TextOut(mHdc, 0, 0, str, 10);
}
