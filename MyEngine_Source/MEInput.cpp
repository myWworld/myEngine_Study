
#include "MEInput.h"

namespace ME{

	std::vector <Input::Key> Input::mKeys = {};

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q','W','E','R','T','Y','U','I','O','P'
		,'A','S','D','F','G','H','J','K','L'
		,'Z','X','C','V','B','N','M',
	};

	void Input::Initialize()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key = {};
			key.bPressed = false;
			key.state = eKeystate::None;
			key.keyCode = (eKeyCode)i;
			
			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0; i < mKeys.size(); i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (mKeys[i].bPressed == true)
				{
					mKeys[i].state = eKeystate::Pressed;
				}
				else
				{
					mKeys[i].state = eKeystate::Down;
				}
				mKeys[i].bPressed = true;
			}
			else
			{
				if(mKeys[i].bPressed == true)
				{
					mKeys[i].state = eKeystate::Up;
				}
				else
				{
					mKeys[i].state = eKeystate::None;
				}
				mKeys[i].bPressed = false;
			}

		}
	}


}
