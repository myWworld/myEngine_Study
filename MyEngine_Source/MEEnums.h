#pragma once

namespace ME::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Items,
		Monster,
		Player,
		Paritcle,
		Max = 16
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End
	};

	enum class eComponentType
	{
		Trasnform,
		SpriteRenderer,
		Animator,
		Script,
		Camera,
		End,
	};
}