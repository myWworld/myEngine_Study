#pragma once
#include "CommonInclude.h"
#include "MEEntity.h"

namespace ME
{
	class GameObject;
	class Component : public Entity
	{
	public:
			
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }


	private:
		GameObject* mOwner;
	};

}

