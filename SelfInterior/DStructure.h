#pragma once
#include "DShape.h"
class DStructure :
	public DShape
{
public:
	DStructure(int mode);
	~DStructure();
	WCHAR* m_fileDoor;
	WCHAR* m_fileRefri;

	void OnDraw(CDC *MemDC);
};

