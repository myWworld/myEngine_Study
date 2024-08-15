#pragma once
#include "MEComponent.h"

namespace ME
{
	using namespace ME::math;

	class Camera:public Component
	{
	public:

		Vector2 CalculatePosition(Vector2 pos) 
		{
			return Vector2(pos - mDistance);
		}
		
		Camera();
		~Camera();

		void Initialize() override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		

	private:

		//std::vector<GameObject*> mGameObjects;

		Vector2 mDistance;
		Vector2 mResolution;
		Vector2 mLookPosition;
		
		GameObject* mTarget;
	
	};

}
