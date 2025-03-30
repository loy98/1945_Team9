#pragma once
#include "config.h"
#include "Singleton.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
public:
	void Init();
	void Release();
	Image* AddImage(wstring key, const wchar_t* filePath, int width, int height,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	Image* AddImage(wstring key, const wchar_t* filePath, int width, int height,
		int maxFrameX, int maxFrameY, bool isFlip = FALSE, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void DeleteImage(wstring key);
	Image* FindImage(wstring key);

private:
	map<wstring, Image*> mapImages;

};

