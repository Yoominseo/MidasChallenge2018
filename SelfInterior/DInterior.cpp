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

	// ��Ʈ�� ���ҽ� �ε�
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

	// �޸� DC�� ����
	pOldBmp = cdc.SelectObject(&bmp);

	// �޸� DC�� ��� �ִ� ��Ʈ���� ȭ�� DC�� �����Ͽ� ���
	MemDC->BitBlt(100, 100, 800, 85, &cdc, 0, 0, SRCCOPY);

	cdc.SelectObject(pOldBmp);
}