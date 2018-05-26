#pragma once
#include "DShape.h"
#include "define.h"

class DWall :
	public DShape
{
public:
	DWall(int mode);
	DWall(CPoint point);
	~DWall();
	void OnDraw(CDC *MemDC);
	void setPoint(CPoint point);
	
	Point m_ptPrev;
	Point m_ptCur;
	bool m_bIsOpen = false;
};

