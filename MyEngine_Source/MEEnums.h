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
		Particle,
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
		Collider,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		End,
	};
}