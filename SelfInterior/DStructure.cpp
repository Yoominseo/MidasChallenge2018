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
	MemDC->BitBlt(100, 100, 800, 85, &cdc, 0, 0, SRCCOPY);

	cdc.SelectObject(pOldBmp);
}
