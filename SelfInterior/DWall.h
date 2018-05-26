#pragma once
#include "DShape.h"
#include "define.h"

class DWall :
	public DShape
{
public:
	DWall();
	DWall(CPoint point);
	~DWall();
	void OnDraw(CDC *MemDC);
	void setPoint(CPoint point);
	
	//프로그램상 POINT
	Point m_ptPrev;
	Point m_ptCur;

	//실제 window POINT
	POINT m_wptPrev; 
	POINT m_wptCur;
};

