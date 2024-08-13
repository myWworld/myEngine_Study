
#include "MEScenes.h"

namespace ME
{
	Scene::Scene()
	{

	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{

	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}

	void Scene::Update()
	{
	//	for (size_t i = 0; i < mGameObjects.size(); i++)
	//	{
	//		mGameObjects[i]->Update();
	//	}
		//������� for��
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}
	void Scene::Render(HDC mHdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render(mHdc);
		}
	}
}