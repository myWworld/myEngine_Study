#pragma once
#include "../MyEngine_Source/MEScript.h"

namespace ME
{


	class PlayerScript :public Script
	{
	public:

		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:
		bool isJump;
		int jumpSeconds;
	};
}

