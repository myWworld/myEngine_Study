
#include "MEScenes.h"

namespace ME
{
	Scene::Scene()
		:mLayers{}
	{
		Scene::createLayers();
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

	void Scene::AddGameObject(GameObject* gameObject, const enums::eLayerType type)
	{
		mLayers[(UINT)type]->AddGameObject(gameObject);
	}

	void Scene::createLayers()
	{
		mLayers.resize((UINT)enums::eLayerType::Max);

		for (size_t i = 0; i < (UINT)enums::eLayerType::Max; i++)
		{
			mLayers[i] = new Layer();
		}
	}
}