#include "stdafx.h"
#include "DInterior.h"
#include "define.h"


DInterior::DInterior(int mode)
{
	m_iShapeMode = mode;
}


DInterior::~DInterior()
{
}

void DInterior::OnDraw(CDC *MemDC)
{
	CDC cdc;
	BITMAP bmpInfo;

	cdc.CreateCompatibleDC(MemDC);

	// 비트맵 리소스 로딩
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	if (m_iShapeMode == TV_MODE)
	{
		bmp.LoadBitmapW(323);
	}
	else
	{
		bmp.LoadBitmapW(325);
	}

	// 메모리 DC에 선택
	pOldBmp = cdc.SelectObject(&bmp);

	// 메모리 DC에 들어 있는 비트맵을 화면 DC로 복사하여 출력
	MemDC->BitBlt(100, 100, 800, 85, &cdc, 0, 0, SRCCOPY);

	cdc.SelectObject(pOldBmp);
}