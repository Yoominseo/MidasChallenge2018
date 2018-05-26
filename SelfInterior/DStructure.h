#pragma once
#include "DShape.h"
class DStructure :
	public DShape
{
public:
	DStructure(int mode, CPoint point);
	~DStructure();

	void OnDraw(CDC *MemDC);
};

