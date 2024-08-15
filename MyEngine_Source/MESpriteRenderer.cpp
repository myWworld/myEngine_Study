#include "MESpriteRenderer.h"
#include "MEGameObject.h"
#include "METransform.h"
#include "CommonInclude.h"
#include "METexture.h"
#include "MERenderer.h"
#include "MECamera.h"

namespace ME {

	ME::SpriteRenderer::SpriteRenderer() 
		:mSize(Vector2::One)
		,mTexture(nullptr)
		,Component(enums::eComponentType::SpriteRenderer)
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
		if (mTexture == nullptr)
			assert(false);


		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = renderer::mainCamera->CalculatePosition(pos);

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect(pos.x, pos.y, mTexture->GedWidth()*mSize.x, mTexture->GetHeight() * mSize.y));
			
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
		
			TransparentBlt(hdc, pos.x, pos.y,
				mTexture->GedWidth(), mTexture->GetHeight()
				, mTexture->GedHdc(), 0, 0
				, mTexture->GedWidth()*mSize.x , mTexture->GetHeight()* mSize.y, RGB(255, 0, 255));
		}
		
	
	}

	
}