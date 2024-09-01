#include "MEUIHUD.h"
#include "MEResources.h"

namespace ME
{
	ME::UIHUD::UIHUD()
		:UIBase(enums::eUIType::HpBar)
	{
	}

	ME::UIHUD::~UIHUD()
	{
	}

	void ME::UIHUD::OnInit()
	{
		SetPos(Vector2(20.0f, 20.0f));
		SetSize(Vector2(0.3f, 0.3f));

		mTexture = Resources::Find<graphics::Texture>(L"HPBAR");
	}

	void ME::UIHUD::OnActive()
	{
	}

	void ME::UIHUD::OnInActive()
	{
	}

	void ME::UIHUD::OnUpdate()
	{
	}

	void ME::UIHUD::OnLateUpdate()
	{
	}

	void ME::UIHUD::OnRender(HDC hdc)
	{
		TransparentBlt(hdc
			, mPosition.x, mPosition.y
			, mPosition.x + mSize.x
			, mPosition.y + mSize.y
			, mTexture->GedHdc()
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, RGB(255, 0, 255));
	}

	void ME::UIHUD::OnClear()
	{
	}

}