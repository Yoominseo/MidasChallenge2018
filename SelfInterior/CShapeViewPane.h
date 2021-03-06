#pragma once

#include "CShapeViewCtrl.h"
// CShapeViewPane

class CShapeViewPane : public CDockablePane
{
	DECLARE_DYNAMIC(CShapeViewPane)

public:
	CShapeViewPane();
	virtual ~CShapeViewPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CShapeViewCtrl m_ctrlShapeView;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


