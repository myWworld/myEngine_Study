#include "MEUIButton.h"
#include "MEInput.h"

namespace ME
{
	UIButton::UIButton()
		:UIBase(enums::eUIType::Button)
	{
	}
	UIButton::~UIButton()
	{
	}
	void UIButton::OnInit()
	{
		SetPos(Vector2(100, 250));
		SetSize(Vector2(100, 204));

		mOnClick = std::bind(&UIButton::ButtonClick, this);

	}
	void UIButton::OnActive()
	{
	}
	void UIButton::OnInActive()
	{
	}
	void UIButton::OnUpdate()
	{
		Vector2 mousePos = Input::GetMousePos();

		if (mousePos.x >= mPosition.x && mousePos.x <= mPosition.x + mSize.x
			&& mousePos.y >= mPosition.y && mousePos.y <= mPosition.y + mSize.y)
		{
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}

		if (Input::GetKeyDown(eKeyCode::LeftMous))
		{
			if(mbMouseOn)
				mOnClick();
		}
	}
	void UIButton::OnLateUpdate()
	{
	}
	void UIButton::OnRender(HDC hdc)
	{
		Rectangle(hdc
			, (int)mPosition.x, (int)mPosition.y
			, mPosition.x + mSize.x, mPosition.y + mSize.y);
	}
	void UIButton::OnClear()
	{
	}
	void UIButton::ButtonClick()
	{
		int a = 0;
	}
}