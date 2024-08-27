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
			mTiles.push_back(tile);
		}


		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}

		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
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
	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;

		_wfopen_s(&pFile, szFilePath, L"wb");
		
		for (Tile * tile: mTiles)
		{
			
			Transform* tr = tile->GetComponent<Transform>();
			TileMapRenderer* tmr = tile->GetComponent<TileMapRenderer>();

			Vector2 sourceIndex;
			sourceIndex = tmr->GetIndex();

			Vector2 position;
			position = tr->GetPosition();

			int x = (int)sourceIndex.x;
			int y = (int)sourceIndex.y;

			fwrite(&x, sizeof(int), 1, pFile);
			fwrite(&y, sizeof(int), 1, pFile);

			x = (int)position.x;
			y = (int)position.y;

			fwrite(&x, sizeof(int), 1, pFile);
			fwrite(&y, sizeof(int), 1, pFile);
		}

		fclose(pFile);

	}

	void ToolScene::Load()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;

		_wfopen_s(&pFile, szFilePath, L"rb");

		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;


			if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) == NULL)
				break;

			Tile* tile = object::Instantiate<Tile>(enums::eLayerType::Tile);
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();

			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SPRINGFLOOR"));
			tmr->SetIndex(Vector2(idxX, idxY));

			tile->SetPosition(posX, posY);


			mTiles.push_back(tile);
		}



		fclose(pFile);
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