#include "MEApplication.h"
#include "MEInput.h"
#include "METime.h"
#include "MESceneManager.h"

namespace ME 
{

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
	
		 adjustWindowRect(hwnd, width, height);
		 createBuffer(width, height);
		 initializeEtc();
		
		 SceneManager::Initialize();
		 
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

		SceneManager::Update();

		
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
	
		ClearRenderTarget();

		Time::Render(mBackHdc);
		
		SceneManager::Render(mHdc);

		CopyRenderTarget(mBackHdc, mHdc);
		
	
	}

	void Application::ClearRenderTarget()
	{
		Rectangle(mBackHdc, -1, -1, 1601, 901);
	}

	void Application::CopyRenderTarget(HDC source, HDC dest)
	{
		//백버퍼에 있는 것을 원본 버퍼에 복사
		BitBlt(dest, 0, 0, mWidth, mHeight,
			source, 0, 0, SRCCOPY);

	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);


		RECT rect = { 0,0,width,height };

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth,mHeight, 0);
		ShowWindow(mHwnd, true);

	}
	void Application::createBuffer(UINT width, UINT height)		//윈도우 해상도에 맞ㄴ느 백퍼버(도화지)생성
	{
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);

	}
	void Application::initializeEtc()
	{
		Input::Initialize();
		Time::Intialize();

	}

}
