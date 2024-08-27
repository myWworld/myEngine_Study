#include "MEApplication.h"
#include "MEInput.h"
#include "METime.h"
#include "MESceneManager.h"
#include "MEResources.h"
#include "MECollisionManager.h"


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
		
		 CollisionManager::Iniatialize();
		 SceneManager::Initialize();
		 
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

   		CollisionManager::Update();
		SceneManager::Update();

		
	}

	void Application::LateUpdate()
	{	
		CollisionManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
	
		ClearRenderTarget();

		Time::Render(mBackHdc);
		
		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

		CopyRenderTarget(mBackHdc, mHdc);
		
	
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Release()
	{
		SceneManager::Release();
		Resources::Release();


	}

	void Application::ClearRenderTarget()
	{

		HBRUSH grayBrush = (HBRUSH)CreateSolidBrush(RGB(128,128,128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);

		Rectangle(mBackHdc, -1, -1, 1601, 901);

		SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);

	}

	void Application::CopyRenderTarget(HDC source, HDC dest)
	{
		//����ۿ� �ִ� ���� ���� ���ۿ� ����
		BitBlt(dest, 0, 0, mWidth, mHeight,
			source, 0, 0, SRCCOPY);

	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);


		RECT rect = { 0,0,width,height };

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);



		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth,mHeight, 0);
		ShowWindow(mHwnd, true);

	}
	void Application::createBuffer(UINT width, UINT height)		//������ �ػ󵵿� �¤��� ���۹�(��ȭ��)����
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
