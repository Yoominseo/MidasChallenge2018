#pragma once


// DShape

#include <gdiplusgraphics.h>

class DShape : public CWnd
{
	DECLARE_DYNAMIC(DShape)

public:
	DShape();
	virtual ~DShape();
	virtual void OnDraw(CDC *MemDC) = 0;
	WCHAR * ConvertMultibyteToUnicode(char * pMultibyte);
	void setRect(int x, int y, int width, int height);
	void setXY(int x, int y);
	
	int m_iShapeMode; //Space, Structure, Interior을 구분 (enum 사용)
	int m_iShapeType; //m_iShapeMode가 SPACE_MODE면, SPACE TPYE을 구분(HOUSE, ROOM)
	Rect m_rect;

private :
	void Swap(void *n1, void *n2);

protected:
	DECLARE_MESSAGE_MAP()
};


