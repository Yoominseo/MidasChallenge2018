
// SelfInteriorView.cpp : implementation of the CSelfInteriorView class
//

#include "stdafx.h"
#include "define.h"
#include <Winuser.h>
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

	//임시로 WALL_MODE설정.
	m_ishape_mode = WALL_MODE;
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
		if (shape->m_iShapeMode == WALL_MODE) 
		{
			DWall *wall = (DWall *)shape;
			wall->OnDraw(&MemDC);
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

//모양(WALL, STRUCTURE, INTERIOR)에 대한 클래스를 추가함.
void CSelfInteriorView::AddShape(CPoint point)
{
	if (m_ishape_mode == WALL_MODE)
	{
		DWall *wall = new DWall();
		m_listShape.AddTail((DShape *)wall);
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

//선(WALL)을 그릴때 90도로 그을 수 있는 최적의 좌표를 찾는 함수
POINT CSelfInteriorView::OptimumPoint(POINT ptPrev, POINT ptCur)
{
	POINT ptResult;
	int pnm = 5;
	int x1 = ptPrev.x;
	int y1 = ptPrev.y;
	int x2 = ptCur.x;
	int y2 = ptCur.y;

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx < pnm && dx > -(pnm)) //x값의 차이가 pmn 아래일때; 
	{
		ptResult.x = x1; //x값은 변함x; 
		ptResult.y = y2; //y값은 현재의 값으로; 
	}
	else if (dy < pnm && dy > -(pnm)) //y값의 차이가 pmn아래일때; 
	{
		ptResult.x = x2;//x값은 현재의 값으로;
		ptResult.y = y1; //y값은 변함x; 
	}
	else //둘중 어디에도 해당하지 않는 경우; 
	{
		ptResult = ptCur;
	}

	return ptResult;
}

//선(WALL)을 처음 그릴때, 주변에 점을 찾아 POINT리턴
POINT CSelfInteriorView::FindPoint(POINT ptCur)
{
	int pnm = 5;
	POINT ptResult = ptCur;
	POSITION ps = m_listPoint.GetHeadPosition();

	while (ps)
	{
		POINT pt = m_listPoint.GetAt(ps);
		int x1 = pt.x;
		int y1 = pt.y;
		int x2 = ptCur.x;
		int y2 = ptCur.y;

		int dx = x2 - x1;
		int dy = y2 - y1;

		if (dx < pnm && dx > -(pnm) && dy < pnm && dy > -(pnm)) //x값의 차이가 pmn 아래일때; 
		{
			ptResult = pt;
			break;
		}
		
		m_listShape.GetNext(ps);
	}

	return ptResult;
}

void CSelfInteriorView::ListAdd(POINT pt)
{
	POSITION ps = m_listShape.GetHeadPosition();
	TRACE("------------------\r\n");

	while (ps)
	{

		POINT point = m_listPoint.GetAt(ps);
		TRACE("%d, %d\r\n", pt.x, pt.y);

		if (point.x == pt.x && point.y == pt.y)
		{
			TRACE("FAILD ADDTAIL %d %d\r\n", pt.x, pt.y);
			return;
		}

		m_listShape.GetNext(ps);
	}

	TRACE("ADDTAIL %d %d\r\n",pt.x, pt.y);
	m_listPoint.AddTail(pt);

	return;
}

// CSelfInteriorView message handlers

void CSelfInteriorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_ptPrev = point;
	AddShape(m_ptPrev);

	GetCursorPos(&m_wptPrev);

	TRACE("m_wptPrev.x = %d, m_wptPrev.y = %d\r\n", m_wptPrev.x, m_wptPrev.y);

	CView::OnLButtonDown(nFlags, point);
}

void CSelfInteriorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	POINT ptCur;
	GetCursorPos(&ptCur);
	TRACE("prev\r\n");
	ListAdd(m_wptPrev);
	TRACE("Cur\r\n");
	ListAdd(ptCur);

#if 1
	TRACE("total -------%d\r\n",m_listPoint.GetCount());

	POSITION ps = m_listShape.GetHeadPosition();

	while (ps)
	{
		POINT point = m_listPoint.GetAt(ps);

		TRACE("%d %d\r\n", point.x, point.y);

		m_listShape.GetNext(ps);
	}
#endif

	m_ptPrev = -1;
	m_wptPrev.x = -1;
	m_wptPrev.y = -1;
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
		POSITION shapeIndex;
		shapeIndex = m_listShape.GetTailPosition();

		if (m_ishape_mode == WALL_MODE)
		{
			DWall *wall = new DWall(m_ptPrev);
			POINT ptCur,ptResult;
			GetCursorPos(&ptCur);
			ptResult = OptimumPoint(m_wptPrev, ptCur);
			SetCursorPos(ptResult.x, ptResult.y);

			wall->setPoint(point);

			m_listShape.SetAt(shapeIndex, (DShape *)wall);
			Invalidate(FALSE);
		}
		else if (m_ishape_mode == STRUCTURE_MODE)
		{
			DStructure *structure = new DStructure();

			m_listShape.SetAt(shapeIndex, (DShape *)structure);
			Invalidate(FALSE);
		}
		else if (m_ishape_mode == INTERIOR_MODE)
		{
			DInterior *interior = new DInterior();

			m_listShape.SetAt(shapeIndex, (DShape *)interior);
			Invalidate(FALSE);
		}
	}
	else if (m_ishape_mode == WALL_MODE) 
	{
		POSITION ps = m_listShape.GetHeadPosition();

		while (ps)
		{
			POINT ptCur, pt, ptResult;
			pt = m_listPoint.GetAt(ps);
			GetCursorPos(&ptCur);
			ptResult = FindPoint(ptCur);

			if (pt.x == ptResult.x && pt.y == ptResult.y)
			{
				SetCursorPos(ptResult.x, ptResult.y);

				break;
			}

			m_listShape.GetNext(ps);
		}
	}

	CView::OnMouseMove(nFlags, point);
}
