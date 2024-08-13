
#include "MEScenes.h"

namespace ME
{
	Scene::Scene()
		:mLayers{}
	{
		Scene::CreateLayers();
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->Initialize();
		}
	}

	void Scene::Update()
	{

		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->Update();
		}
	}
	void Scene::LateUpdate()
	{

		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;

			layer->LateUpdate();
		}
	}
	void Scene::Render(HDC mHdc)
	{
		
			for (Layer* layer : mLayers)
			{
				if (layer == nullptr)
					continue;

				layer->Render(mHdc);
			}
	}

	void Scene::OnEnter()
	{

	 }
	void Scene::OnExit()
	{

	 }

	void Scene::AddGameObject(GameObject* gameObject, const eLayerType type)
	{
		mLayers[(UINT)type]->AddGameObject(gameObject);
	}
	void Scene::CreateLayers()
	{
		mLayers.resize((UINT)eLayerType::Max);

		for (size_t i = 0; i < (UINT)eLayerType::Max; i++)
		{
			mLayers[i] = new Layer();
		}
	}
}