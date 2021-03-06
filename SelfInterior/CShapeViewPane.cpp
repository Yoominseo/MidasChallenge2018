// CShapeViewPane.cpp : implementation file
//

#include "stdafx.h"
#include "SelfInterior.h"
#include "CShapeViewPane.h"


// CShapeViewPane

IMPLEMENT_DYNAMIC(CShapeViewPane, CDockablePane)

CShapeViewPane::CShapeViewPane()
{

}

CShapeViewPane::~CShapeViewPane()
{
}


BEGIN_MESSAGE_MAP(CShapeViewPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CShapeViewPane message handlers




int CShapeViewPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	if (!m_ctrlShapeView.Create(IDD_SHAPE, this))
	{
		TRACE("문자열 출력 윈도우를 만들지 못했습니다.\n");
		return -1;
	}
	
	m_ctrlShapeView.ShowWindow(SW_SHOW);
	return 0;
}


void CShapeViewPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if (m_ctrlShapeView.GetSafeHwnd())
	{
		m_ctrlShapeView.MoveWindow(0, 0, cx, cy);
		m_ctrlShapeView.SetFocus();
	}
}
