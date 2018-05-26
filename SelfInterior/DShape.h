#pragma once


// DShape

class DShape : public CWnd
{
	DECLARE_DYNAMIC(DShape)

public:
	DShape();
	virtual ~DShape();

	virtual void OnDraw(CDC *MemDC) = 0;
	void Swap(void *n1, void *n2) 
	{
		void *temp;
		temp = n1;
		n1 = n2;
		n2 = temp;
	};
	int m_iShapeMode; //Space, Structure, Interior을 구분 (enum 사용)
	int m_iShapeType; //m_iShapeMode가 SPACE_MODE면, SPACE TPYE을 구분(HOUSE, ROOM)
	//CRect m_rect;

protected:
	DECLARE_MESSAGE_MAP()
};


