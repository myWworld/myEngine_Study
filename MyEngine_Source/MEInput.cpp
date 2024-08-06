
#include "MEInput.h"

namespace ME{

	std::vector <Input::Key> Input::Keys = {};

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q','W','E','R','T','Y','U','I','O','P'
		,'A','S','D','F','G','H','J','K','L'
		,'Z','X','C','V','B','N','M',
		VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP,
	};

	void Input::CreateKeys()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key = {};
			key.bPressed = false;
			key.state = eKeystate::None;
			key.keyCode = (eKeyCode)i;

			Keys.push_back(key);
		}
	}
	void Input::UpdateKeys()
	{
		for (size_t i = 0; i < Keys.size(); i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (Keys[i].bPressed == true)
				{
					Keys[i].state = eKeystate::Pressed;
				}
				else
				{
					Keys[i].state = eKeystate::Down;
				}
				Keys[i].bPressed = true;
			}
			else
			{
				if (Keys[i].bPressed == true)
				{
					Keys[i].state = eKeystate::Up;
				}
				else
				{
					Keys[i].state = eKeystate::None;
				}
				Keys[i].bPressed = false;
			}

		}
	}
	
	void Input::Initialize()
	{
		CreateKeys();
	}

	void Input::Update()
	{
		UpdateKeys();
	}


}
