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
	DDX_Control(pDX, IDC_STRUCTURE_DOOR, m_btnDoor);
	DDX_Control(pDX, IDC_STRUCTURE_WINDOW, m_btnWindow);
	DDX_Control(pDX, IDC_INTERIOR_TV, m_btnTV);
	DDX_Control(pDX, IDC_INTERIOR_REFI, m_btnREFI);
}


BEGIN_MESSAGE_MAP(CShapeViewCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_STRUCTURE_DOOR, &CShapeViewCtrl::OnBnClickedStructureDoor)
	ON_BN_CLICKED(IDC_STRUCTURE_WINDOW, &CShapeViewCtrl::OnBnClickedStructureWindow)
	ON_BN_CLICKED(IDC_INTERIOR_TV, &CShapeViewCtrl::OnBnClickedInteriorTv)
	ON_BN_CLICKED(IDC_INTERIOR_REFI, &CShapeViewCtrl::OnBnClickedInteriorRefi)
END_MESSAGE_MAP()


// CShapeViewCtrl message handlers



//BOOL CShapeViewCtrl::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  Add extra initialization here
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // EXCEPTION: OCX Property Pages should return FALSE
//}


BOOL CShapeViewCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_btnDoor.LoadBitmaps(IDB_bmp_DOOR);
	m_btnWindow.LoadBitmaps(IDB_bmp_WINDOW);
	m_btnTV.LoadBitmaps(IDB_bmp_TV);
	m_btnREFI.LoadBitmaps(IDB_bmp_REFRI);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CShapeViewCtrl::OnBnClickedStructureDoor()
{
	// TODO: Add your control notification handler code here
}


void CShapeViewCtrl::OnBnClickedStructureWindow()
{
	// TODO: Add your control notification handler code here
}


void CShapeViewCtrl::OnBnClickedInteriorTv()
{
	// TODO: Add your control notification handler code here
}


void CShapeViewCtrl::OnBnClickedInteriorRefi()
{
	// TODO: Add your control notification handler code here
}
