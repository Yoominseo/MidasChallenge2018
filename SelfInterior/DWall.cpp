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
	clr.SetFromCOLORREF(RGB(0, 0, 0));
	Pen pen(Color(clr), 2);

	graphics.DrawLine(&pen, m_ptPrev, m_ptCur);
}

void DWall::setPoint(CPoint point)
{
	m_ptCur.X = point.x;
	m_ptCur.Y = point.y;
}
