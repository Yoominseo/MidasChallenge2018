#include "stdafx.h"
#include "DStructure.h"
#include "define.h"
#include "stdafx.h"


DStructure::DStructure(int mode, CPoint point)
{
	m_iShapeMode = mode;
	m_rect.X = point.x;
	m_rect.Y = point.y;
}

DStructure::~DStructure()
{
}

void DStructure::OnDraw(CDC *MemDC)
{
	CDC cdc;
	BITMAP bmpInfo;

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
	MemDC->BitBlt(m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height, &cdc, 0, 0, SRCCOPY);


	cdc.SelectObject(pOldBmp);
}
