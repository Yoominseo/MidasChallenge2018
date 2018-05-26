// CSettingDlg.cpp : implementation file

#include "stdafx.h"
#include "SelfInterior.h"
#include "CSettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg dialog

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SIZE, pParent)
	, m_strSet_X(_T(""))
	, m_strSet_Y(_T(""))
	, m_strSet_Name(_T(""))
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SizeX, m_strSet_X);
	DDX_Text(pDX, IDC_EDIT_SizeY, m_strSet_Y);
	DDX_Text(pDX, IDC_EDIT_SizeName, m_strSet_Name);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
END_MESSAGE_MAP()


// CSettingDlg message handlers
