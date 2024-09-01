#include "MEUIManager.h"

namespace ME
{
	std::unordered_map<enums::eUIType, UIBase*> mUIs = {};
	std::stack<UIBase*> mUIBases = {};
	std::queue<enums::eUIType> mRequestUIQueue = {};
	UIBase* mActiveUI = {};

	void UIManager::Initailize()
	{
	}
	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;

		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();

			if (uiBase)
			{
				uiBase->Initialize();
				uiBases.pop();
			}


		}
	}
	void UIManager::OnLoad(enums::eUIType type)
	{
		std::unordered_map<enums::eUIType, UIBase*>::iterator iter
		= mUIs.find(type);

		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}
	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;

		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();

			if (uiBase)
			{
				uiBase->Update();
				uiBases.pop();
			}


		}

		if (mRequestUIQueue.size() > 0)
		{
			enums::eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUI);
		}

	}
	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;

		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();

			if (uiBase)
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}


		}
	}
	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		//만약에 현재 추가된 ui가 전체화면이라면 그것말고 모두 비활성화

		if (addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;

			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();

				if (uiBase)
				{
					uiBase->InActive();
					
				}


			}

		}

		mUIBases.push(addUI);
		mActiveUI = nullptr;

	}
	void UIManager::OnFail()
	{
		mActiveUI = nullptr;
	}
	void UIManager::Push(enums::eUIType type)
	{
		mRequestUIQueue.push(type);
	}
	void UIManager::Pop(enums::eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		UIBase* uibase = nullptr;

		while (mUIBases.size() > 0)
		{
			uibase = mUIBases.top();
			mUIBases.pop();


		}
	}
}