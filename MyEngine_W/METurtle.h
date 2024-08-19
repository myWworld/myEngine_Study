#pragma once
#include "../MyEngine_Source/MEGameObject.h"

namespace ME
{
	class Turtle:public GameObject
	{
	public:

		Turtle();
		~Turtle();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:

	};

}
