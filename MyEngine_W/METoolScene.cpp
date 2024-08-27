#include "METoolScene.h"
#include "MEObject.h"
#include "METile.h"
#include "METileMapRenderer.h"
#include "MEResources.h"
#include "MERenderer.h"
#include "MECamera.h"
#include "MEInput.h"

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
		Tile* tile = object::Instantiate<Tile>(enums::eLayerType::Tile);
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

		if (Input::GetKeyDown(eKeyCode::LeftMous))
		{
			Vector2 pos = Input::GetMousePos();
			
		
			int idxX = pos.x / TileMapRenderer::TileSize.x;
			int idxY = pos.y / TileMapRenderer::TileSize.y;

			Tile* tile = object::Instantiate<Tile>(enums::eLayerType::Tile);
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();

			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SPRINGFLOOR"));

			tile->SetPosition(idxX, idxY);

		}

	}
	void ToolScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(mHdc, TileMapRenderer::TileSize.x * i, 0, NULL);
			LineTo(mHdc, TileMapRenderer::TileSize.x *i, 1000);

		}

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(mHdc, 0, TileMapRenderer::TileSize.y * i, NULL);
			LineTo(mHdc,1000, TileMapRenderer::TileSize.y * i);

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


LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{ 
	} 
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		//DC�� ȭ�鿡 ��¿� �ʿ��� ��� ������ ������ ������ ����ü
		//GDI��⿡ ���ؼ� �����ȴ�.
		//� ��Ʈ�� ����� �ǰ�, � ���� ���⸦ �����ٰǰ� � �������� �׷��ٲ���
		//ȭ�� ��¿� �ʿ��� ��� ���� WINAPI������ DC�� ���ؼ� �۾��� ������ �� �ִ�,

		ME::graphics::Texture* texture = ME::Resources::Find<ME::graphics::Texture>(L"SPRINGFLOOR");

		TransparentBlt(hdc
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, texture->GedHdc()
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, RGB(255, 0, 255));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}