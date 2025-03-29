#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
}

void ImageManager::Release()
{
	for (auto p : mapImages)
	{
		if (p.second)
		{
			p.second->Release();
			delete p.second;
			p.second = nullptr;
		}
	}
	mapImages.clear();
	ReleaseInstance();
}

Image* ImageManager::AddImage(wstring key, const wchar_t* filePath, int width, int height, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;
	image = FindImage(key);
	if (image)
		return image;

	image = new Image();
	if (FAILED(image->Init(filePath, width, height, isTransparent, transColor)))
	{
		image->Release();
		delete image;

		return nullptr;
	}
	
	mapImages.insert(make_pair(key, image));

	return image;
}

Image* ImageManager::AddImage(wstring key, const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY, bool isFlip, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;
	image = FindImage(key);
	if (image)
		return image;

	image = new Image();
	if (FAILED(image->Init(filePath, width, height, maxFrameX, maxFrameY, isTransparent, transColor)))
	{
		image->Release();
		delete image;

		return nullptr;
	}

	mapImages.insert(make_pair(key, image));

	return image;
}

//Image* ImageManager::AddImage(wstring key, const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY, bool isFlip, bool isTransparent, bool isFlip, COLORREF transColor)
//{
//	Image* image = nullptr;
//	image = FindImage(key);
//	if (image)
//		return image;
//
//	image = new Image();
//	if (FAILED(image->Init(filePath, width, height, maxFrameX, maxFrameY, isTransparent, transColor)))
//	{
//		image->Release();
//		delete image;
//
//		return nullptr;
//	}
//
//	mapImages.insert(make_pair(key, image));
//
//	return image;
//}

void ImageManager::DeleteImage(wstring key)
{
	auto it = mapImages.find(key);

	if (it == mapImages.end())
		return;

	it->second->Release();
	delete it->second;
	it->second = nullptr;

	mapImages.erase(it);
}

Image* ImageManager::FindImage(wstring key)
{
	auto it = mapImages.find(key);

	if (it == mapImages.end())
		return nullptr;

	return it->second;
}
