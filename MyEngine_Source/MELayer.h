#pragma once

#include "MEEntity.h"
#include "CommonInclude.h"
#include "MEGameObject.h"

namespace ME
{
	class Layer:public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
	private:

		std::vector<GameObject*> mGameObjects;

		typedef std::vector<GameObject*>::iterator GameObjectIter;

	};

}

