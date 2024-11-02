#pragma once
#pragma once
#include "../MyEngine_Source/MEScript.h"

namespace ME
{


	class FireBarScript :public Script
	{
	public:


		FireBarScript();
		~FireBarScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void SetRotation(float rot) { mRot = rot; }

	private:



	private:

		float mRotateTime;

		float mCurRot;
		float mRot;
		
	};

}