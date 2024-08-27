#include "METile.h"

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
}