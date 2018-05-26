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

	// ��Ʈ�� ���ҽ� �ε�
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

	// �޸� DC�� ����
	pOldBmp = cdc.SelectObject(&bmp);

	// �޸� DC�� ��� �ִ� ��Ʈ���� ȭ�� DC�� �����Ͽ� ���
	MemDC->BitBlt(m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height, &cdc, 0, 0, SRCCOPY);


	cdc.SelectObject(pOldBmp);
}
