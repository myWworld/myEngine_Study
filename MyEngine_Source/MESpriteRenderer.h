#pragma once
#include "MEComponent.h"
#include "MEEntity.h"

namespace ME
{

	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

	private:

	};

}
