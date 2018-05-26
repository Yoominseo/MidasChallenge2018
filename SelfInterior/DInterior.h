#pragma once
#include "DShape.h"
#include "define.h"
class DInterior :
	public DShape
{
public:
	DInterior();
	~DInterior();

	void OnDraw(CDC *MemDC);
};

