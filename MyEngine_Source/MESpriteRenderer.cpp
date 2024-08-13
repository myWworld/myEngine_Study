#include "MESpriteRenderer.h"
#include "MEGameObject.h"
#include "METransform.h"
#include "CommonInclude.h"

namespace ME {

	ME::SpriteRenderer::SpriteRenderer() :
		mImage(nullptr)
		, mWidth(0)
		, mHeight(0)
	{
	}

	ME::SpriteRenderer::~SpriteRenderer()
	{
	}

	void ME::SpriteRenderer::Initialize()
	{
	}

	void ME::SpriteRenderer::Update()
	{
	}

	void ME::SpriteRenderer::LateUpdate()
	{
	}

	void ME::SpriteRenderer::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector2 pos = tr->GetPosition();
		
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();

	}

}