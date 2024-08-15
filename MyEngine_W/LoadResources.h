#pragma once

#include "../MyEngine_Source/MEResources.h"
#include "../MyEngine_Source/METexture.h"

namespace ME
{
	void LoadResources()
	{
		
		Resources::Load<graphics::Texture>(L"TITLE", L"..\\Resources\\Title.png");
		Resources::Load<graphics::Texture>(L"MAP", L"..\\Resources\\map.png");
		Resources::Load<graphics::Texture>(L"MARIO", L"..\\Resources\\mario.png");
		Resources::Load<graphics::Texture>(L"QUESTIONBOX", L"..\\Resources\\questionbox.png");
		Resources::Load<graphics::Texture>(L"FLOWER", L"..\\Resources\\flower.png");
		Resources::Load<graphics::Texture>(L"GAMEOVER", L"..\\Resources\\gameover.png");
	}

}