#include "MEApplication.h"


namespace ME {

	Application::Application()
		:mHwnd(nullptr)
		, mHdc(nullptr)
		,mSpeed(0)
	{

	}
	
	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		mPlayer.Update();
	}

	void Application::LateUpdate()
	{

	}

	void Application::Render()
	{
		mPlayer.Render(mHdc);
	
	}
}
