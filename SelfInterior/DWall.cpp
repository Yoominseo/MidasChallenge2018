#include "stdafx.h"
#include "DWall.h"
#include "define.h"


DWall::DWall()
{
	m_iShapeMode = WALL_MODE;
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
	if(m_bIsOpen == false)
		clr.SetFromCOLORREF(RGB(255, 0, 0));
	else 
		clr.SetFromCOLORREF(RGB(0, 0, 0));
	Pen pen(Color(clr), 2);

	graphics.DrawRectangle(&pen, m_rect);
}

void DWall::setPoint(CPoint point)
{
	m_ptCur.X = point.x;
	m_ptCur.Y = point.y;
}
