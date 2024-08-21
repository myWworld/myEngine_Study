#include "MELayer.h"

namespace ME
{
	ME::Layer::Layer()
	{
	}

	ME::Layer::~Layer()
	{

		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}

	void ME::Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Initialize();
		}
	}

	void ME::Layer::Update()
		{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			GameObject::eState state = gameObj->GetActive();
			if (state == GameObject::eState::Dead
					|| state == GameObject::eState::Paused)
			{
				continue;
			}

			gameObj->Update();
		}
	}

	void ME::Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;


			GameObject::eState state = gameObj->GetActive();
			if (state == GameObject::eState::Dead
				|| state == GameObject::eState::Paused)
			{
				continue;
			}

			gameObj->LateUpdate();
		}
	}

	void ME::Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;


			GameObject::eState state = gameObj->GetActive();
			if (state == GameObject::eState::Dead
				|| state == GameObject::eState::Paused)
			{
				continue;
			}

			gameObj->Render(hdc);
		}
	}
	
	void Layer::Destroy()
	{
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			GameObject::eState active = (*iter)->GetActive();

			if (active == GameObject::eState::Dead)
			{
				GameObject* deathObj = (*iter);
				iter = mGameObjects.erase(iter);

				delete deathObj;
				deathObj = nullptr;

				continue;
			}
			
	
			iter++;
			

		}
	}

	void ME::Layer::AddGameObject(GameObject* gameObject)
	{

		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}
}