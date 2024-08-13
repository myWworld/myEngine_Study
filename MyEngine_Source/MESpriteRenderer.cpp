#include "MESpriteRenderer.h"
#include "MEGameObject.h"
#include "METransform.h"

namespace ME {

	ME::SpriteRenderer::SpriteRenderer()
	{
	}

	ME::SpriteRenderer::~SpriteRenderer()
	{
	}

	void ME::SpriteRenderer::Initialize()
	{
	}

	void ME::SpriteRenderer::Update()
	{
	}

	void ME::SpriteRenderer::LateUpdate()
	{
	}

	void ME::SpriteRenderer::Render(HDC hdc)
	{
		HBRUSH blueBrush
			= CreateSolidBrush(RGB(255, 0, 255));

		// 파랑 브러쉬 DC에 선택 그리고 흰색 브러쉬 반환값 반환
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(rand() % 255, rand() % 255, rand() % 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldPen);

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Rectangle(hdc, tr->GetX(), tr->GetY()
			, 100 + tr->GetX(), 100 + tr->GetY());

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}

}