#include "MEEndScene.h"
#include "MEGameObject.h"
#include "MEPlayer.h"
#include "METransform.h"
#include "MESpriteRenderer.h"


ME::EndScene::EndScene()
{
}

ME::EndScene::~EndScene()
{
}

void ME::EndScene::Initialize()
{
	Player* bg = new Player();

	Transform* tr = bg->AddComponent<Transform>();

	tr->SetPos(Vector2(0, 0));
	tr->SetName(L"TR");

	SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();

	sr->SetName(L"SR");
	sr->ImageLoad(L"C:\\Users\\SAMSUNG\\Desktop\\MyEngine\\myEngineforStudy\\Resources\\EndingCredit.png");

	AddGameObject(bg,eLayerType::BackGround);

}

void ME::EndScene::Update()
{
	Scene::Update();
}

void ME::EndScene::LateUpdate()
{
	Scene::LateUpdate();
}

void ME::EndScene::Render(HDC mHdc)
{
	Scene::Render(mHdc);
}
