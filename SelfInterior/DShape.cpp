// DShape.cpp : implementation file
//

#include "stdafx.h"
#include "SelfInterior.h"
#include "DShape.h"
#include <math.h>


// DShape

IMPLEMENT_DYNAMIC(DShape, CWnd)

DShape::DShape()
{

}

DShape::~DShape()
{
}

WCHAR * DShape::ConvertMultibyteToUnicode(char * pMultibyte)
{
	int nLen = strlen(pMultibyte);

	WCHAR* pWideChar = new WCHAR[nLen];
	memset(pWideChar, 0x00, (nLen) * sizeof(WCHAR));

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pMultibyte, -1, pWideChar, nLen);

	return pWideChar;
}

void DShape::setRect(int x, int y, int width, int height)
{
	m_rect.Width = width;
	m_rect.Height = height;
	m_rect.X = x;
	m_rect.Y = y;

	if (width < 0) // 너비가 -일때
	{ 
		m_rect.Width = abs(m_rect.Width);
		if (height < 0)  //너비가 -이고 높이가 -일때
		{
			m_rect.Height = abs(m_rect.Height);
			m_rect.X = x - m_rect.Width;
			m_rect.Y = y - m_rect.Height;
		}
		else
			m_rect.X = x - m_rect.Width;
	}
	else if (height < 0) 
	{
		m_rect.Height = abs(m_rect.Height);
		m_rect.Y = y - m_rect.Height;
	}
}

void DShape::setXY(int x, int y)
{
	m_rect.X = x;
	m_rect.Y = y;
}

void DShape::Swap(void * n1, void * n2)
{
	void *temp;
	temp = n1;
	n1 = n2;
	n2 = temp;
}


BEGIN_MESSAGE_MAP(DShape, CWnd)
END_MESSAGE_MAP()



// DShape message handlers


