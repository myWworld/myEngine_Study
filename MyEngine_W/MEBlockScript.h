#pragma once
#include "../MyEngine_Source/MEScript.h"

namespace ME
{


	class BlockScript :public Script
	{
	public:


		BlockScript();
		~BlockScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;




	private:

		void CannotPass(Collider* obj);

	private:

		bool mbIsOnBlock;
	};

}