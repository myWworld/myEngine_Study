#include "METileMapRenderer.h"
#include "MEGameObject.h"
#include "METransform.h"
#include "CommonInclude.h"
#include "METexture.h"
#include "MERenderer.h"
#include "MECamera.h"


namespace ME {

	ME::TileMapRenderer::TileMapRenderer()
		:mSize(Vector2(3.0f,3.0f))
		, mTexture(nullptr)
		, Component(enums::eComponentType::SpriteRenderer)
		, mIndex(Vector2::One )
		, mTileSize(16.0f, 16.0f)
	{
	}

	ME::TileMapRenderer::~TileMapRenderer()
	{
	}

	void ME::TileMapRenderer::Initialize()
	{
	}

	void ME::TileMapRenderer::Update()
	{
	}

	void ME::TileMapRenderer::LateUpdate()
	{
	}

	void ME::TileMapRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			assert(false);


		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Vector2 scale = tr->GetScale();
		float rot = tr->GetRotation();

		if(renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

	
		if(mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			HDC imgHdc = mTexture->GedHdc();

			if (mTexture->IsAlpha())
			{
				//�������� ȿ���� ���Ҷ�
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = 0;
				func.SourceConstantAlpha = 255;


				AlphaBlend(hdc
					, pos.x
					, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GedHdc()
					, mIndex.x * mTileSize.x
					, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, pos.x
					, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GedHdc()
					, mIndex.x * mTileSize.x
					, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, RGB(255, 0, 255));
			}
		}


	}


}
