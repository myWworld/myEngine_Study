#include "METoolScene.h"
#include "MEObject.h"
#include "METile.h"
#include "METileMapRenderer.h"
#include "MEResources.h"
#include "MERenderer.h"
#include "MECamera.h"

namespace ME
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		GameObject* tile = object::Instantiate<Tile>(enums::eLayerType::Tile);
		TileMapRenderer *tmr = tile->AddComponent<TileMapRenderer>();
		
		tmr->SetTexture(Resources::Find<graphics::Texture>(L"SPRINGFLOOR"));
		
		Scene::Initialize();


	}
	void ToolScene::Update()
	{
		Scene::Update();
	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ToolScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(mHdc, 16 * 3 * i, 0, NULL);
			LineTo(mHdc, 16* 3 *i, 1000);

		}

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(mHdc, 0, 16 * 3 * i, NULL);
			LineTo(mHdc,1000, 16 * 3 * i);

		}
	}
	void ToolScene::Destroy()
	{
		Scene::Destroy();
	}
	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
}