#include "MEApplication.h"
#include "MEInput.h"

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

		Input::Initialize();
	

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
