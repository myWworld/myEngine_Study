#pragma once

#include "../MyEngine_Source/MEResources.h"
#include "../MyEngine_Source/METexture.h"

namespace ME
{
	void LoadResources()
	{
		
		Resources::Load<graphics::Texture>(L"TITLE", L"..\\Resources\\Title1.png");
		Resources::Load<graphics::Texture>(L"STAGE1_1", L"..\\Resources\\statge1_1.png");
		Resources::Load<graphics::Texture>(L"MEGAMAN", L"..\\Resources\\Megaman.png");
		//::Load<graphics::Texture>(L"QUESTIONBOX", L"..\\Resources\\questionbox.png");
	//	Resources::Load<graphics::Texture>(L"FLOWER", L"..\\Resources\\flower.png");
		Resources::Load<graphics::Texture>(L"GAMEOVER", L"..\\Resources\\gameover.png");
		Resources::Load<graphics::Texture>(L"BULLETEFFECT", L"..\\Resources\\BulletEffect.png");
	}

}