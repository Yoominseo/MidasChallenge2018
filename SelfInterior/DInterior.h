#pragma once
#include "DShape.h"
#include "define.h"
class DInterior :
	public DShape
{
public:
	DInterior(int mode);
	~DInterior();

	void OnDraw(CDC *MemDC);
};

