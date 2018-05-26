#include "stdafx.h"
#include "DSpace.h"
#include "define.h"


DSpace::DSpace()
{
	m_iShapeMode = SPACE_MODE;
}


DSpace::~DSpace()
{
}

void DSpace::OnDraw(CDC *MemDC)
{
	Graphics graphics(*MemDC);

	Gdiplus::Color clr;
	clr.SetFromCOLORREF(RGB(0, 0, 0));
	Pen pen(Color(clr), 2);

	graphics.DrawRectangle(&pen, m_rect);
}

