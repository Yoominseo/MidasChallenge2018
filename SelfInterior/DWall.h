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
	
	//���α׷��� POINT
	Point m_ptPrev;
	Point m_ptCur;

	//���� window POINT
	POINT m_wptPrev; 
	POINT m_wptCur;
};

