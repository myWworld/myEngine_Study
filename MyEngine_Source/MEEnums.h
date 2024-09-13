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
		Aura,
		Player,
		Floor,
		Stair,
		Chimney,
		Flag,
		Block,
		Particle,
		Max = 20
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

	enum class eUIType
	{
		HpBar,
		Score,
		Button,
		End,
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
		AudioListener,
		AudioSource,
		End,
	};
}