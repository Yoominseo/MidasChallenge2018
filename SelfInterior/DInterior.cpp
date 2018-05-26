#include "stdafx.h"
#include "DInterior.h"
#include "define.h"


DInterior::DInterior(int mode, CPoint point)
{
	m_iShapeMode = mode;
	m_rect.X = point.x;
	m_rect.Y = point.y;
}


DInterior::~DInterior()
{
}

void DInterior::OnDraw(CDC *MemDC)
{
	Graphics graphics(*MemDC);

	Gdiplus::Color clr;

	Pen pen(Color(clr), 2);

	graphics.DrawRectangle(&pen, m_rect);

	CDC cdc;
	BITMAP bmpInfo;

	cdc.CreateCompatibleDC(MemDC);

	// ��Ʈ�� ���ҽ� �ε�
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	

	if (m_iShapeMode == TV_MODE)
	{

		m_rect.Height = 80;
		m_rect.Width = 80;
		bmp.LoadBitmapW(323);
		CRect rect;
		rect.top = m_rect.GetBottom() + 20;
		rect.bottom = rect.top + 20;
		rect.right = m_rect.GetRight();
		rect.left = m_rect.GetLeft();
		MemDC->DrawText(_T("TV"), rect, DT_SINGLELINE);

	}
	else
	{
		m_rect.Height = 80;
		m_rect.Width = 80;
		bmp.LoadBitmapW(325);
		CRect rect;
		rect.top = m_rect.GetBottom() + 20;
		rect.bottom = rect.top + 20;
		rect.right = m_rect.GetRight();
		rect.left = m_rect.GetLeft();
		MemDC->DrawText(_T("�����"), rect, DT_SINGLELINE);
	}

	// �޸� DC�� ����
	pOldBmp = cdc.SelectObject(&bmp);

	// �޸� DC�� ��� �ִ� ��Ʈ���� ȭ�� DC�� �����Ͽ� ���
	
	MemDC->BitBlt(m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height, &cdc, 0, 0, SRCCOPY);
	Sleep(1);

	cdc.SelectObject(pOldBmp);
}