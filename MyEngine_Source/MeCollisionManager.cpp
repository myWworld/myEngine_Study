#include "MECollisionManager.h"
#include "MEScenes.h"
#include "MESceneManager.h"
#include "MECollider.h"

namespace ME
{
	 std::bitset<(UINT)enums::eLayerType::Max> mCollisionLayerMatrix[(UINT)enums::eLayerType::Max] = {};
	void ME::CollisionManager::Iniatialize()
	{
	}

	void ME::CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)enums::eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)enums::eLayerType::Max; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true);
				{
					LayerCollision(scene, (enums::eLayerType)row, (enums::eLayerType)col);
				}
			}
		}
	}

	void ME::CollisionManager::LateUpdate()
	{
	}

	void ME::CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::CollisionLayerCheck(enums::eLayerType left, enums::eLayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{

	}

	void CollisionManager::LayerCollision(Scene* scene, enums::eLayerType left, enums::eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObject();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObject();

		for (GameObject* left: lefts )
		{
			if (left->IsActive() == false)
			{
				continue;
			}

			Collider* leftCol = left->GetComponent<Collider>();

			if (leftCol == nullptr)
			{
				continue;
			}

		

			for (GameObject* right : rights)
			{
				{
					if (right->IsActive() == false)
					{
						continue;
					}

					Collider* rightCol = right->GetComponent<Collider>();
					
					if (rightCol == nullptr)
					{
						continue;
					}


				if (left == right)
					continue;

				ColliderCollision(leftCol,rightCol);
			}
		}

}