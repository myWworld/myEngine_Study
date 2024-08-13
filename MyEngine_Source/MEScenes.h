#pragma once
#include "CommonInclude.h"
#include "MEEntity.h"
#include "MEGameObject.h"
#include "MELayer.h"


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

		
		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObject, const eLayerType type);

	private:
		void CreateLayers();

		std::vector<Layer*> mLayers;
	};

}
