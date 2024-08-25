#pragma once
#include "../MyEngine_Source/MEScript.h"
#include "../MyEngine_Source/MEGameObject.h"
#include "MEBullet.h"
#include "CommonInclude.h"
#include "MEPlayerScript.h"
#include "../MyEngine_Source/MECollider.h"

namespace ME
{


	class BulletScript:public Script
	{
	public:

		BulletScript();
		~BulletScript();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;
		void Destroy();

		void OnCollisionEnter( Collider* other) ;
		void OnCollisionStay( Collider* other) ;
		void OnCollisionExit( Collider* other) ;

		void SetPlayer(GameObject* gameObj) { mPlayer = gameObj; }
	

	private:


	private:

		GameObject* mPlayer;
	};

}
