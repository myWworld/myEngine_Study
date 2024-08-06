#include "MEApplication.h"
#include "MEInput.h"
#include "METime.h"

namespace ME {

	Application::Application()
		:mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		,mBackBuffer(nullptr)
		,mBackHdc(nullptr)
		,mSpeed(0)
	{

	}
	
	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);


		RECT rect = {0,0,width,height};


		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, nullptr, 0, 0
			, rect.right - rect.left, 
			rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);

		//윈도우 해상도에 맞ㄴ느 백퍼버(도화지)생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);

		Input::Initialize();
		Time::Intialize();

	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		mPlayer.Update();
	
	}

	void Application::LateUpdate()
	{

	}

	void Application::Render()
	{
	
		Rectangle(mBackHdc, 0, 0, 1600, 900);

		Time::Render(mBackHdc);
		mPlayer.Render(mBackHdc);
	
		//백버퍼에 있는 것을 원본 버퍼에 복사
		BitBlt(mHdc, 0, 0, mWidth, mHeight,
			mBackHdc, 0, 0, SRCCOPY);
		
	}
}
