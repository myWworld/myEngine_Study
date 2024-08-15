#include "METexture.h"
#include "MEApplication.h"

extern ME::Application application;

namespace ME::graphics
{


	Texture::Texture()
		:Resource(enums::eResourceType::Texture)
	{

	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		//bmp 일때
		std::wstring ext 
			= path.substr(path.find_last_of(L".") + 1);
		

		//png 일때
			
		if (ext == L"png")
		{
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());

			if (mImage == nullptr) { return S_FALSE; }

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		else if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP,
				0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr) { return S_FALSE; }

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(oldBitmap);

		}

	

		return S_OK;
	}

}