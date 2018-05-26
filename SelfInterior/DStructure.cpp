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

	// 비트맵 리소스 로딩
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

	// 메모리 DC에 선택
	pOldBmp = cdc.SelectObject(&bmp);

	// 메모리 DC에 들어 있는 비트맵을 화면 DC로 복사하여 출력
	MemDC->BitBlt(100, 100, 800, 85, &cdc, 0, 0, SRCCOPY);

	cdc.SelectObject(pOldBmp);
}
