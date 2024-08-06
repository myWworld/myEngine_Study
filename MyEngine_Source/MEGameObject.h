#pragma once
#include "CommonInclude.h"


namespace ME {
	class GameObject
	{
	public:
		GameObject();
		~GameObject();


		void Update();
		void LateUpdate();
		void Render(HDC hdc);



	private:

		float mX;
		float mY;

	};

}
	