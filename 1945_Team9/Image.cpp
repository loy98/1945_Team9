#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, 
    bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = 0;
    imageInfo->maxFrameY = 0;
    imageInfo->frameWidth = 0;
    imageInfo->frameHeight = 0;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    //imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);        // ��� ����� ���� ����
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

void Image::Render(HDC hdc, int destX, int destY)
{
    int x = destX - imageInfo->width / 2;
    int y = destY - imageInfo->height / 2;
    if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            x, y,
            imageInfo->width, imageInfo->height,
            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,                // ���� ������ DC
            destX, destY,       // ���� ������ ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // ���� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameIndex, bool isFlip)
{
    imageInfo->currFrameX = frameIndex;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            (imageInfo->frameHeight * imageInfo->currFrameY) + (imageInfo->frameHeight - 1),
            -imageInfo->frameWidth, imageInfo->frameHeight,
            SRCCOPY
        );

        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hTempDC,
            0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,
            destX, destY,
            imageInfo->width / 9,
            imageInfo->height,
            imageInfo->hMemDC,
            imageInfo->width / 9 * frameIndex, 0,
            SRCCOPY
        );
    }
}

void Image::FrameRender(HDC hdc, int destX, int destY, int frameX, int frameY, bool isFlip)
{
    imageInfo->currFrameX = frameX;
    imageInfo->currFrameY = frameY;

    int x = destX - imageInfo->frameWidth / 2;
    int y = destY - imageInfo->frameHeight / 2;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            (imageInfo->frameHeight * imageInfo->currFrameY) + (imageInfo->frameHeight - 1),
            imageInfo->frameWidth, -imageInfo->frameHeight,
            SRCCOPY
        );

        GdiTransparentBlt(hdc,
            x, y,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hTempDC,
            0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            x, y,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,
            x, y,
            imageInfo->frameWidth,
            imageInfo->height,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX, 
            imageInfo->frameHeight * imageInfo->currFrameY,
            SRCCOPY
        );
    }
}

// Test
void Image::TestRender(HDC hdc, int destX, int destY, float frameY, bool isFlip)
{
    if (isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0,
            WINSIZE_X, WINSIZE_Y * (WINSIZE_X / 310.f),
            imageInfo->hMemDC,
            0, 6114 - (WINSIZE_Y * (frameY + 1)),
            310, WINSIZE_Y,
            SRCCOPY
        );

        GdiTransparentBlt(hdc,
            destX, destY,
            WINSIZE_X, WINSIZE_Y,

            imageInfo->hTempDC,
            0, 0,
            WINSIZE_X, WINSIZE_Y,
            transColor);
    }
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
        DeleteObject(imageInfo->hTempBit);
        DeleteDC(imageInfo->hTempDC);

        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        delete imageInfo;
        imageInfo = nullptr;
    }
}
