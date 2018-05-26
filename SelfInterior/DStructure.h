#pragma once
#include "DShape.h"
class DStructure :
	public DShape
{
public:
	DStructure();
	~DStructure();
	void OnDraw(CDC *MemDC);
};

