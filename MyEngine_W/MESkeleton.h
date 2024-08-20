#pragma once
#include "../MyEngine_Source/MEGameObject.h"

namespace ME
{


	class Skeleton:public GameObject
	{
	public:


	void Initialize() override;
	void Update()override;
	void LateUpdate()override;
	void Render(HDC hdc)override;


	private:
	};

}
