#pragma once

namespace ME::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Items,
		Player,
		Max = 16
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		End
	};

	enum class eComponentType
	{
		Trasnform,
		SpriteRenderer,
		Script,
		Camera,
		End,
	};
}