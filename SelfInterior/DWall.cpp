#include "stdafx.h"
#include "DWall.h"
#include "define.h"


DWall::DWall(int mode)
{
	m_iShapeMode = mode;
}

DWall::DWall(CPoint point)
{
	m_iShapeMode = WALL_MODE;
	m_ptPrev.X = point.x;
	m_ptPrev.Y = point.y;
}


DWall::~DWall()
{
}

void DWall::OnDraw(CDC * MemDC)
{
	Graphics graphics(*MemDC);

	Gdiplus::Color clr;
#if 0
	if(m_bIsOpen == false)
		clr.SetFromCOLORREF(RGB(255, 0, 0));
	else
#endif
		clr.SetFromCOLORREF(RGB(0, 0, 0));
	Pen pen(Color(clr), 2);

	graphics.DrawRectangle(&pen, m_rect);
}

void DWall::setPoint(CPoint point)
{
	m_ptCur.X = point.x;
	m_ptCur.Y = point.y;
}
