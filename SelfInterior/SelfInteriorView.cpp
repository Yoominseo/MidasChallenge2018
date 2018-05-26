
// SelfInteriorView.cpp : implementation of the CSelfInteriorView class
//

#include "stdafx.h"
#include "define.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SelfInterior.h"
#endif

#include "SelfInteriorDoc.h"
#include "SelfInteriorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSelfInteriorView

IMPLEMENT_DYNCREATE(CSelfInteriorView, CView)

BEGIN_MESSAGE_MAP(CSelfInteriorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSelfInteriorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CSelfInteriorView construction/destruction

CSelfInteriorView::CSelfInteriorView()
{
	// TODO: add construction code here

	//임시로 SPACE_MODE설정.
	m_ishape_mode = SPACE_MODE;
}

CSelfInteriorView::~CSelfInteriorView()
{
}

BOOL CSelfInteriorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSelfInteriorView drawing

void CSelfInteriorView::OnDraw(CDC* /*pDC*/)
{
	CSelfInteriorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSelfInteriorView printing


void CSelfInteriorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSelfInteriorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSelfInteriorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSelfInteriorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSelfInteriorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSelfInteriorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSelfInteriorView diagnostics

#ifdef _DEBUG
void CSelfInteriorView::AssertValid() const
{
	CView::AssertValid();
}

void CSelfInteriorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSelfInteriorDoc* CSelfInteriorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSelfInteriorDoc)));
	return (CSelfInteriorDoc*)m_pDocument;
}
#endif //_DEBUG

// 사용자정의 함수

void CSelfInteriorView::AddShape(CPoint point)
{
	switch (m_ishape_mode)
	{
	case SPACE_MODE:
		DSpace * space = new DSpace();
		m_listShape.AddTail((DShape *)space);
		break;
	case STRUCTURE_MODE:
		DStructure * space = new DStructure();
		m_listShape.AddTail((DShape *)space);
		break;
	case INTERIOR_MODE:
		DInterior * space = new DInterior();
		m_listShape.AddTail((DShape *)space);
		break;
	}
}

// CSelfInteriorView message handlers

void CSelfInteriorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_ptPrev = point;

	CView::OnLButtonDown(nFlags, point);
}

void CSelfInteriorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
}


void CSelfInteriorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDblClk(nFlags, point);
}




void CSelfInteriorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (nFlags == MK_LBUTTON)
	{
		switch (m_ishape_mode)
		{

		}
	}
	/*if (m_draw_mode == CLASS_MODE && nFlags == MK_LBUTTON) { //사각형그릴때
		DMakeclass *makeclass = new DMakeclass();
		makeclass->SetRect(m_ptPrev.x, m_ptPrev.y, point.x - m_ptPrev.x, point.y - m_ptPrev.y);

		POSITION Index;
		Index = m_list.GetTailPosition();
		m_list.SetAt(Index, (Diagram *)makeclass);

		Invalidate(FALSE);
	}*/

	CView::OnMouseMove(nFlags, point);
}
