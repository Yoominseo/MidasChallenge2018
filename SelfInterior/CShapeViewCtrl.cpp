// CShapeViewCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SelfInterior.h"
#include "CShapeViewCtrl.h"
#include "afxdialogex.h"


// CShapeViewCtrl dialog

IMPLEMENT_DYNAMIC(CShapeViewCtrl, CDialogEx)

CShapeViewCtrl::CShapeViewCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAPE, pParent)
{

}

CShapeViewCtrl::~CShapeViewCtrl()
{
}

void CShapeViewCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPACE_HOUSE, m_btnHome);
}


BEGIN_MESSAGE_MAP(CShapeViewCtrl, CDialogEx)
//	ON_BN_CLICKED(IDC_SPACE_HOUSE, &CShapeViewCtrl::OnBnClickedSpaceHouse)
ON_WM_CREATE()
ON_BN_CLICKED(IDC_SPACE_HOUSE, &CShapeViewCtrl::OnBnClickedSpaceHouse)
END_MESSAGE_MAP()


// CShapeViewCtrl message handlers


//void CShapeViewCtrl::OnBnClickedSpaceHouse()
//{
//	// TODO: Add your control notification handler code here
//}

BOOL CShapeViewCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
