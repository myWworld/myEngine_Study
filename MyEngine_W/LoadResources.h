#pragma once

#include "../MyEngine_Source/MEResources.h"
#include "../MyEngine_Source/METexture.h"
#include "../MyEngine_Source/MEAudioClip.h"

namespace ME
{
	void LoadResources()
	{
		
		Resources::Load<graphics::Texture>(L"TITLE", L"..\\Resources\\Title.png");
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

		Resources::Load<graphics::Texture>(L"COIN", L"..\\Resources\\Coin.png");
		Resources::Load<graphics::Texture>(L"QBOX", L"..\\Resources\\Qbox.png");
		Resources::Load<graphics::Texture>(L"USEDQBOX", L"..\\Resources\\Usedqbox.png");
		Resources::Load<graphics::Texture>(L"STAR", L"..\\Resources\\Star.png");

		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\Hpbar.png");
		Resources::Load<graphics::Texture>(L"STARTBUTTON", L"..\\Resources\\StartButton.png");
		Resources::Load<graphics::Texture>(L"REDTRIANGLE", L"..\\Resources\\redTriangle.png");

		Resources::Load<graphics::Texture>(L"CANNON", L"..\\Resources\\cannon.png");


		Resources::Load<graphics::Texture>(L"STAREFFECT", L"..\\Resources\\StarEffect.png");

		Resources::Load<AudioClip>(L"MARIOJUMPSOUND", L"..\\Resources\\MarioJump.mp3");

			
	}

}