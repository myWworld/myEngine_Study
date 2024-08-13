#pragma once
#include "CommonInclude.h"
#include "MEEntity.h"
#include "MEGameObject.h"

namespace ME 
{

	class Scene : public Entity
	{
	public:

		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC mHdc);

		void AddGameObject(GameObject * gameObject);

	private:
		std::vector<GameObject*> mGameObjects;
	};

}
