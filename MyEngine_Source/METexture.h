#pragma once
#include "MEResource.h"

namespace ME::graphics
{

	class Texture: public Resource
	{
	public:
		enum class eTextureType
		{
			Bmp,
			Png,
			None,
		};

		Texture();
		~Texture();
		
		virtual HRESULT Load(const std::wstring& path) override;

		UINT GedWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GedHdc() { return mHdc; }
		eTextureType GetTextureType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:

		eTextureType mType;

		Gdiplus::Image* mImage;
		HBITMAP mBitmap;
		HDC mHdc;

		UINT mWidth;
		UINT mHeight;
	};
}

