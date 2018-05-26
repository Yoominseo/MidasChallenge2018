#pragma once
#include "DShape.h"
class DStructure :
	public DShape
{
public:
	DStructure(int mode);
	~DStructure();

	void OnDraw(CDC *MemDC);
};

