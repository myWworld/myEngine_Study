#pragma once
#include "CommonInclude.h"
#include "MEBoxCollider2D.h"
#include "MECircleCollider2D.h"


namespace ME
{
	class CollisionManager
	{
	public:

		static void Iniatialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void CollisionLayerCheck(enums::eLayerType left, enums::eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, enums::eLayerType left, enums::eLayerType right);
		static void ColliderCollision(Collider* left, Collider* right);

	private:


		static std::bitset<(UINT)enums::eLayerType::Max> mCollisionLayerMatrix[(UINT)enums::eLayerType::Max];
	};
}

