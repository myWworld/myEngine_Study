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

		 
		 void SetRotation(float rot) { mRot = rot; }
		 Vector2 GetCentralPoint() { return mCentralPoint; }

		 bool IsRotate() { return mbIsRotate; }
		 float GetHeight() { return mHeight; }
		 float GetWidth() { return mWidth; }

	private:
	
		Vector2 RotateCollider(float rot, int x, int y, int width, int height, HDC hdc);
	
	private:
		
		float mRot;
		Vector2 mCentralPoint;

		float mWidth, mHeight;

		bool mbIsRotate;

	};

}
