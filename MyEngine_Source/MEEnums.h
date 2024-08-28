#pragma once

namespace ME::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Tile,
		Items,
		Monster,
		Player,
		Floor,
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

	enum class eColliderType
	{
		Rect2D,
		Circle2D,
	};

	enum class eComponentType
	{
		Trasnform,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		End,
	};
}