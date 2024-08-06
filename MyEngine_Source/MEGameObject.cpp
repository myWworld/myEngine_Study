#include "MEGameObject.h"
#include "MEInput.h"
#include "METime.h"

namespace ME {

	GameObject::GameObject() {

	}

	GameObject::~GameObject() {

	}
	void GameObject::Update()
	{
		const int speed = 100.0f;

		if (Input::GetKey(eKeyCode::A) || Input::GetKey(eKeyCode::Left))
		{
			mX -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D))
		{
			mX += speed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			mY -= speed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mY += speed * Time::DeltaTime();
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