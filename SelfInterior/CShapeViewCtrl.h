#pragma once


// CShapeViewCtrl dialog

class CShapeViewCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeViewCtrl)

public:
	CShapeViewCtrl(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CShapeViewCtrl();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CBitmapButton m_btnROOM;
	CBitmapButton m_btnDOOR;
	CBitmapButton m_btnWINDOW;
	CBitmapButton m_btnREFRI;
	CBitmapButton m_btnTV;

	afx_msg void OnBnClickedStructureDoor();
	afx_msg void OnBnClickedStructureWindow();
	afx_msg void OnBnClickedInteriorRefri();
	afx_msg void OnBnClickedInteriorTv();

	afx_msg void OnBnClickedSpaceRoom();
};
