#include "stdafx.h"
#include "DStructure.h"
#include "define.h"
#include "stdafx.h"


DStructure::DStructure(int mode)
{
	m_iShapeMode = mode;
	CString door = _T("./res/img_door.bmp");
	CString refri = _T("./res/img_window.bmp");
	m_fileDoor = ConvertMultibyteToUnicode((LPSTR(LPCTSTR(door))));
	m_fileRefri = ConvertMultibyteToUnicode((LPSTR(LPCTSTR(refri))));
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
		bmp.LoadBitmapW(328);
	}
	else
	{
		bmp.LoadBitmapW(330);
	}

	// �޸� DC�� ����
	pOldBmp = cdc.SelectObject(&bmp);

	// �޸� DC�� ��� �ִ� ��Ʈ���� ȭ�� DC�� �����Ͽ� ���
	MemDC->BitBlt(100, 100, 800, 85, &cdc, 0, 0, SRCCOPY);

	cdc.SelectObject(pOldBmp);
}
