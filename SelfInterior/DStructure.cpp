#include "stdafx.h"
#include "DStructure.h"
#include "define.h"
#include "stdafx.h"


DStructure::DStructure(int mode)
{
	m_iShapeMode = mode;
}

DStructure::~DStructure()
{
}

void DStructure::OnDraw(CDC *MemDC)
{
	CDC cdc;
	BITMAP bmpInfo;
	m_rect.X = 100;
	m_rect.Y = 100;

	cdc.CreateCompatibleDC(MemDC);

	// 비트맵 리소스 로딩
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	if (m_iShapeMode == DOOR_MODE)
	{
		m_rect.Width = 80;
		m_rect.Height = 80;
		bmp.LoadBitmapW(328);
	}
	else
	{
		m_rect.Height = 20;
		m_rect.Width = 80;
		bmp.LoadBitmapW(330);
	}

	// 메모리 DC에 선택
	pOldBmp = cdc.SelectObject(&bmp);

	// 메모리 DC에 들어 있는 비트맵을 화면 DC로 복사하여 출력
	MemDC->BitBlt(100, 100, 800, 85, &cdc, 0, 0, SRCCOPY);

	cdc.SelectObject(pOldBmp);
}
