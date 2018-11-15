#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{

}

HRESULT imageManager::init(void)
{

	return S_OK;
}

void imageManager::release(void)
{
	deleteAll();
}


image* imageManager::addImage(string strKey, int width, int height, BOOL alphablend)
{
	image* img = findImage(strKey);

	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �������� ��.!
	img = new image;

	if (FAILED(img->init(width, height, alphablend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addTransImage(string strKey, int width, int height, bool trans, COLORREF transColor, BOOL alphablend)
{
	image* img = findImage(strKey);

	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �������� ��.!
	img = new image;

	if (FAILED(img->initTrans(width, height, trans, transColor, alphablend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, BOOL alphablend)
{
	image* img = findImage(strKey);

	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �������� ��.!
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor, alphablend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, BOOL alphablend)
{
	image* img = findImage(strKey);

	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �������� ��.!
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor, alphablend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alphablend)
{
	image* img = findImage(strKey);

	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �������� ��.!
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor, alphablend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alphablend)
{
	image* img = findImage(strKey);

	//�̹����� �̹� �ִٸ� �� �̹����� ��ȯ
	if (img) return img;
	//�װ� �ƴ϶�� ���μ����� ������� �������� ��.!
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor, alphablend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//ã�Ҵ�
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//���� �̹����� �߰�
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}


BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//�̹��� ������ �ִ�!
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;
}

BOOL imageManager::deleteAllButBackBuffer(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->first == "backBuffer")
		{
			++iter;
			continue;
		}
		else if (iter->first == "pixelBuffer")
		{
			++iter;
			continue;
		}
		else if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	return TRUE;
}

void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaFrameRender(hdc, destX, destY, alpha);
}

void imageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void imageManager::alphaLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaLoopRender(hdc, drawArea, offSetX, offSetY, alpha);
}

void imageManager::renderTile(string strKey, HDC hdc, int destX, int destY, int sourXNum, int sourYNum, int tileSpace, int tileWidth)
{
	image* img = findImage(strKey);

	GdiTransparentBlt
	(hdc,
		destX,
		destY,
		tileWidth,
		tileWidth,
		img->getMemDC(),
		sourXNum * (tileWidth + tileSpace), sourYNum * (tileWidth + tileSpace),
		tileWidth, tileWidth,
		RGB(255, 0, 255));
}

void imageManager::renderTile(string strKey, HDC hdc, int destX, int destY, int sourXNum, int sourYNum, int tileSpace, int mapTileWidth, int imageTileWidth)
{
	image* img = findImage(strKey);
	
	GdiTransparentBlt
	(hdc,
		destX,
		destY,
		mapTileWidth,
		mapTileWidth,
		img->getMemDC(),
		sourXNum * (imageTileWidth + tileSpace), sourYNum * (imageTileWidth + tileSpace),
		imageTileWidth, imageTileWidth,
		RGB(255, 0, 255));
		/*
	BitBlt
	(hdc,
		destX, destY,
		mapTileWidth, mapTileWidth,
		img->getMemDC(),
		sourXNum * (imageTileWidth + tileSpace), sourYNum * (imageTileWidth + tileSpace),
		SRCCOPY);
		*/
}

void imageManager::renderPixelTile(string strKey, HDC hdc, int destX, int destY, int sourXNum, int sourYNum, int tileSpace, int mapTileWidth, int imageTileWidth, COLORREF rgb)
{
	image* img = findImage(strKey);

	GdiTransparentBlt
	(hdc,
		destX,
		destY,
		mapTileWidth,
		mapTileWidth,
		img->getMemDC(),
		sourXNum * (imageTileWidth + tileSpace), sourYNum * (imageTileWidth + tileSpace),
		imageTileWidth, imageTileWidth,
		rgb);
}

void imageManager::renderTile(string strKey, HDC hdc, int destX, int destY, int sourXNum, int sourYNum, int tileSpace, int mapTileWidth, int mapTileHeight, int imageTileWidth, int imageTileHeight)
{
	image* img = findImage(strKey);

	GdiTransparentBlt
	(hdc,
		destX,
		destY,
		mapTileWidth,
		mapTileHeight,
		img->getMemDC(),
		sourXNum * (imageTileWidth + tileSpace), sourYNum * (imageTileHeight + tileSpace),
		imageTileWidth, imageTileHeight,
		RGB(255, 0, 255));
}