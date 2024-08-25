#include "MECollisionManager.h"
#include "MEScenes.h"
#include "MESceneManager.h"
#include "MECollider.h"

namespace ME
{
	 std::bitset<(UINT)enums::eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)enums::eLayerType::Max] = {};
	 std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};
	 
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


	void CollisionManager::LayerCollision(Scene* scene, enums::eLayerType left, enums::eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObject();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObject();

		for (GameObject* left : lefts)
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

					ColliderCollision(leftCol, rightCol);
				}
			}

		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		//�� �浹ü ��ȣ�� ������ ID�� Ȯ���ؼ� CollisionId ���� ����
		CollisionID id = {  };

		id.left = left->GetID();
		id.right = right->GetID();

		//�ش� id�� �浹ü ������ �˻����ش�.
		//���࿡ �浹ü ������ ���ٸ� �浹������ ����

		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert({ id.id, false });
			iter = mCollisionMap.find(id.id);
		}

		//�浹üũ�� ���ָ�ȴ�.

		if (Intersect(left, right))
		{
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);

				iter->second = true;
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;


		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		if (leftType == enums::eColliderType::Rect2D
			&& rightType == enums::eColliderType::Rect2D)
		{
			//AABB �浹 rect-rect
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
			{
				return true;
			}
		}

		if (leftType == enums::eColliderType::Circle2D
			&& rightType == enums::eColliderType::Circle2D)
		{
			//circle - circle
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);

			float distance = (leftCirclePos - rightCirclePos).length();

			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}

		}

		if (leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
		{
			//circle - rect
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);

			float r = leftSize.x / 2.0f;


			if ( (leftCirclePos.x >= rightPos.x - r && leftCirclePos.x <= rightPos.x + r) 
				&& (leftCirclePos.y >= rightPos.y - r && leftCirclePos.y <= rightPos.y + r))
			{
				return true;
			}
			
		}


		if (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D)
		{
			//circle - rect
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);

			float r = rightSize.x / 2.0f;


			if ((rightCirclePos.x >= leftPos.x - r && rightCirclePos.x <= leftPos.x + r)
				&& (rightCirclePos.y >= leftPos.y - r && rightCirclePos.y <= leftPos.y + r))
			{
				return true;
			}

		}


		return false;
	}

}