#include "MEGameObject.h"
#include "MEInput.h"

namespace ME {

	GameObject::GameObject() {

	}

	GameObject::~GameObject() {

	}
	void GameObject::Update()
	{


		if (Input::GetKey(eKeyCode::A))
		{
			mX -= 0.01f;
		}

		if (Input::GetKey(eKeyCode::D))
		{
			mX += 0.01f;
		}
		if (Input::GetKey(eKeyCode::W))
		{
			mY -= 0.01f;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mY += 0.01f;
		}

	}
	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		SelectObject(hdc, brush);

		Rectangle(hdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);

		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}


}