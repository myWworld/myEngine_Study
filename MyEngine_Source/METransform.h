#pragma once
#include "CommonInclude.h"
#include "MEEntity.h"
#include "MEComponent.h"

namespace ME
{
	struct Pos
	{
		int mX;
		int mY;
	};

	class Transform: public Component
	{
	public:

		Transform();
		~Transform();
		
		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
		
		void SetPos(float x, float y) { mX = x; mY = y; }
		int GetX() { return mX; }
		int GetY() { return mY; }

	private:
		int mX;
		int mY;
	};

}
