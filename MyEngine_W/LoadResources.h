#pragma once

#include "../MyEngine_Source/MEResources.h"
#include "../MyEngine_Source/METexture.h"

namespace ME
{
	void LoadResources()
	{
		
		Resources::Load<graphics::Texture>(L"TITLE", L"..\\Resources\\Title1.png");
		Resources::Load<graphics::Texture>(L"STAGE1_1", L"..\\Resources\\statge1_1.png");

		Resources::Load<graphics::Texture>(L"MEGAMANR", L"..\\Resources\\MegamanR.png");
		Resources::Load<graphics::Texture>(L"MEGAMANL", L"..\\Resources\\MegamanL.png");

		Resources::Load<graphics::Texture>(L"MUSHROOML", L"..\\Resources\\MushRoomL.png");
		Resources::Load<graphics::Texture>(L"MUSHROOMR", L"..\\Resources\\MushRoomR.png");

		Resources::Load<graphics::Texture>(L"SKELETONR", L"..\\Resources\\SkeletonR.png");
		Resources::Load<graphics::Texture>(L"SKELETONL", L"..\\Resources\\SkeletonL.png");

		//::Load<graphics::Texture>(L"QUESTIONBOX", L"..\\Resources\\questionbox.png");
	//	Resources::Load<graphics::Texture>(L"FLOWER", L"..\\Resources\\flower.png");
		Resources::Load<graphics::Texture>(L"GAMEOVER", L"..\\Resources\\gameover.png");

		Resources::Load<graphics::Texture>(L"BULLETL", L"..\\Resources\\BulletL.png");
		Resources::Load<graphics::Texture>(L"BULLETR", L"..\\Resources\\BulletR.png");

		Resources::Load<graphics::Texture>(L"SPRINGFLOOR", L"..\\Resources\\SpringFloor.bmp");
	}

}