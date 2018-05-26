
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

void CSelfInteriorView::OnDraw(CDC* pDC)
{
	CSelfInteriorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CDC MemDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	CRect rect;
	GetClientRect(&rect);

	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

#if 0
	Graphics graphics(MemDC);
	Rect m_rect;

	Gdiplus::Color clr;
	clr.SetFromCOLORREF(RGB(0, 0, 0));
	Pen pen(Color(clr), 2);
	m_rect.X = 50;
	m_rect.Y = 50;
	m_rect.Width = 100;
	m_rect.Height = 100;

	graphics.DrawRectangle(&pen, m_rect);
#endif

	POSITION ps = m_listShape.GetHeadPosition();

	while (ps) 
	{
		DShape *shape;
		shape = m_listShape.GetAt(ps);
		if (shape->m_iShapeMode == SPACE_MODE) 
		{
			DSpace *space = (DSpace *)shape;
			space->OnDraw(&MemDC);
		}
		m_listShape.GetNext(ps);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY); //memdc를 dc에 한번에 넣어서 더블버퍼링 기법 구현

	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
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
	if (m_ishape_mode == SPACE_MODE)
	{
		DSpace *space = new DSpace();
		m_listShape.AddTail((DShape *)space);
	}
	else if (m_ishape_mode == STRUCTURE_MODE)
	{
		DStructure *structure = new DStructure();
		m_listShape.AddTail((DShape *)structure);
	}
	else if (m_ishape_mode == INTERIOR_MODE)
	{
		DInterior *interior = new DInterior();
		m_listShape.AddTail((DShape *)interior);
	}

}

// CSelfInteriorView message handlers

void CSelfInteriorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_ptPrev = point;
	AddShape(point);

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
		POSITION Index;
		Index = m_listShape.GetTailPosition();

		if (m_ishape_mode == SPACE_MODE)
		{
			DSpace *space = new DSpace();

			space->setRect(m_ptPrev.x, m_ptPrev.y, point.x - m_ptPrev.x, point.y - m_ptPrev.y);

			m_listShape.SetAt(Index, (DShape *)space);
			Invalidate(FALSE);
		}
		else if (m_ishape_mode == STRUCTURE_MODE)
		{
			DStructure *structure = new DStructure();

			m_listShape.SetAt(Index, (DShape *)structure);
			Invalidate(FALSE);
		}
		else if (m_ishape_mode == INTERIOR_MODE)
		{
			DInterior *interior = new DInterior();

			m_listShape.SetAt(Index, (DShape *)interior);
			Invalidate(FALSE);
		}
	}

	CView::OnMouseMove(nFlags, point);
}
