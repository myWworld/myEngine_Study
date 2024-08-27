#include "METile.h"
#include "METransform.h"
#include "METileMapRenderer.h"

namespace ME
{
	ME::Tile::Tile()
	{
	}

	ME::Tile::~Tile()
	{
	}

	void ME::Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void ME::Tile::Update()
	{
		GameObject::Update();
	}

	void ME::Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ME::Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Tile::SetPosition(int x, int y)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos;
		pos.x =  x * TileMapRenderer::TileSize.x;
		pos.y =  y * TileMapRenderer::TileSize.y;

		tr->SetPosition(pos);
	}
}