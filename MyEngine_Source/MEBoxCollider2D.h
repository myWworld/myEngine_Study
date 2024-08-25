#pragma once
#include "MECollider.h"

namespace ME
{


	class BoxCollider2D:public Collider
	{
	public:

		BoxCollider2D();
		~BoxCollider2D();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		 void Render(HDC hdc)override;

	private:

		Vector2 mSize;
	};

}
