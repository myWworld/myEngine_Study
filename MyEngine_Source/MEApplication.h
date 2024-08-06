#pragma once

#include "CommonInclude.h"
#include "MEGameObject.h"

namespace ME
{
	class Application
	{

	public:

		Application();
		~Application();

		void Initialize(HWND hwnd, UINT width, UINT height);
		void Run();

		void Update();
		void LateUpdate();
		void Render();

	private:

		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBuffer;

		UINT mWidth;
		UINT mHeight;

		float mSpeed;


		GameObject mPlayer;
	};

}

