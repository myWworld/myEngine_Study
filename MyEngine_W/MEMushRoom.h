#pragma once
#include "../MyEngine_Source/MEGameObject.h"

namespace ME
{
	class MushRoom:public GameObject
	{
	public:

		MushRoom();
		~MushRoom();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:

	};

}
