
// SelfInteriorView.h : interface of the CSelfInteriorView class
//

#pragma once

#include "DShape.h"
#include "DStructure.h"
#include "DInterior.h"
#include "DWall.h"
#include "SelfInteriorDoc.h"

class CSelfInteriorView : public CView
{
protected: // create from serialization only
	CSelfInteriorView();
	DECLARE_DYNCREATE(CSelfInteriorView)

// Attributes
public:
	CSelfInteriorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSelfInteriorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CPoint m_ptPrev;
	int m_ishape_mode;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSendMessage(WPARAM wParam, LPARAM lPraram);
	CList<DShape *> m_listShape;
	CList<POINT> m_listPoint;

	//사용자 정의 함수
	void AddShape(CPoint);
	POINT OptimumPoint(POINT ptPrev, POINT ptCur);
	POINT FindPoint(POINT ptCur);
	void ListAdd(POINT pt);
	CPoint CSelfInteriorView::magnet(int cx, int cy);

	afx_msg void OnFileSave();
	afx_msg void OnHelpHelp();
	afx_msg void OnEditRedo();
	afx_msg void OnEditUndo();
	CList<DShape*> m_listShape_bak;
};

#ifndef _DEBUG  // debug version in SelfInteriorView.cpp
inline CSelfInteriorDoc* CSelfInteriorView::GetDocument() const
   { return reinterpret_cast<CSelfInteriorDoc*>(m_pDocument); }
#endif

