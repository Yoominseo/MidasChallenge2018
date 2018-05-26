#pragma once
#include "DShape.h"
class DSpace :
	public DShape
{
public:
	DSpace();
	~DSpace();
	void OnDraw(CDC *MemDC);
};

