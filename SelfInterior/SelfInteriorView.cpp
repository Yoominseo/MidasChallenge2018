
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

#include "CHelpDlg.h"
#include "SelfInteriorDoc.h"
#include "SelfInteriorView.h"
#include "CShapeViewCtrl.h"


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
	ON_MESSAGE(WM_SHAPE_MESSAGE, OnSendMessage)
	ON_COMMAND(ID_FILE_SAVE, &CSelfInteriorView::OnFileSave)
	ON_COMMAND(ID_HELP_HELP, &CSelfInteriorView::OnHelpHelp)
	ON_COMMAND(ID_EDIT_REDO, &CSelfInteriorView::OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CSelfInteriorView::OnEditUndo)
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
		else if (shape->m_iShapeMode == DOOR_MODE || shape->m_iShapeMode == WINDOW_MODE)
		{
			DStructure *structure = (DStructure *)shape;
			structure->OnDraw(&MemDC);
		}
		else if (shape->m_iShapeMode == TV_MODE || shape->m_iShapeMode == REFRI_MODE)
		{
			DInterior *interior = (DInterior *)shape;
			interior->OnDraw(&MemDC);
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
		DWall *wall = new DWall(m_ishape_mode);
		m_listShape.AddTail((DShape *)wall);
		Invalidate(FALSE);
	}
	else if (m_ishape_mode == DOOR_MODE)
	{
		point.y -= 80;
		DStructure *structure = new DStructure(m_ishape_mode, point);
		m_listShape.AddTail((DShape *)structure);
		Invalidate(FALSE);
	}
	else if ( m_ishape_mode == WINDOW_MODE)
	{
		point.y -= 10;
		DStructure *structure = new DStructure(m_ishape_mode, point);
		m_listShape.AddTail((DShape *)structure);
		Invalidate(FALSE);
	}
	else if (m_ishape_mode == TV_MODE || m_ishape_mode == REFRI_MODE)
	{
		DInterior *interior = new DInterior(m_ishape_mode, point);
		m_listShape.AddTail((DShape *)interior);
		Invalidate(FALSE);
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

CPoint CSelfInteriorView::magnet(int cx, int cy)
{
	int size = 20;

	int tmp_x = cx % size;
	int tmp_y = cy % (size /2);

	int x, y;


	if (tmp_x < size/2)
	{
		x = cx - tmp_x;
	}
	else
	{
		x = cx + size - tmp_x;
	}

	if (tmp_y < size/4)
	{
		y = cy - tmp_y;
	}
	else
	{
		y = cy + size/2 - tmp_y;
	}

	return CPoint(x, y);
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

	CPoint magentPoint;
	magentPoint = magnet(point.x, point.y);
	m_ptPrev = magentPoint;
	AddShape(m_ptPrev);

	CView::OnLButtonDown(nFlags, point);
}

void CSelfInteriorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	TRACE("m_ ptPrev : %d %d\r\n", m_ptPrev.x, m_ptPrev.y);
	TRACE("m_ ptCur : %d %d\r\n", point.x, point.y);

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
			DWall *wall = new DWall(m_ishape_mode);


			CPoint magentPoint;
			magentPoint = magnet(point.x, point.y);

			wall->setRect(m_ptPrev.x, m_ptPrev.y, magentPoint.x - m_ptPrev.x, magentPoint.y - m_ptPrev.y);

			POSITION Index;
			Index = m_listShape.GetTailPosition();

			m_listShape.SetAt(shapeIndex, (DShape *)wall);
			Invalidate(FALSE);
		}
	}

	CView::OnMouseMove(nFlags, point);
}

LRESULT CSelfInteriorView::OnSendMessage(WPARAM wParam, LPARAM lPraram)
{
	int mode = (int)wParam;
	m_ishape_mode = mode;
	
	return LRESULT();
}

bool SaveBMP(CDC* pDC, CRect BitmapSize, int BitCount, CString filename)
{
	CDC memDC;
	CBitmap Bitmap, *pOldBmp;

	HANDLE handle;
	HANDLE hDIB;
	HPALETTE hPal = NULL;

	BITMAP bm;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;

	DWORD dwLen;

	//----- CDC의 내용을 Bitmap으로 전송 ----
	memDC.CreateCompatibleDC(pDC);
	Bitmap.CreateCompatibleBitmap(pDC, BitmapSize.Width(), BitmapSize.Height());
	pOldBmp = (CBitmap*)memDC.SelectObject(&Bitmap);
	memDC.BitBlt(0, 0, BitmapSize.Width(), BitmapSize.Height(), pDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBmp);

	//------------------------- 비트멥 헤더를 기록함 -------------------------
	if (hPal == NULL)
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

	GetObject(HBITMAP(Bitmap), sizeof(BITMAP), &bm);

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = BitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = bm.bmWidth * bm.bmHeight * 3;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	int nColors = (1 << bi.biBitCount);
	if (nColors > 256)
		nColors = 0;

	dwLen = bi.biSize + nColors * sizeof(RGBQUAD);

	hPal = SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);

	RealizePalette(pDC->GetSafeHdc());

	hDIB = GlobalAlloc(GMEM_FIXED, dwLen);

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	GetDIBits(pDC->GetSafeHdc(), HBITMAP(Bitmap), 0, (DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	if (bi.biSizeImage == 0)
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;

	dwLen += bi.biSizeImage;

	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	GetDIBits(pDC->GetSafeHdc(), HBITMAP(Bitmap), 0, (DWORD)bi.biHeight,
		(LPBYTE)lpbi + (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	BITMAPFILEHEADER hdr;

	hdr.bfType = ((WORD)('M' << 8) | 'B');
	hdr.bfSize = (DWORD)(GlobalSize(hDIB) + sizeof(hdr));
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));

	char* pBmpBuf;
	DWORD FileSize;
	FileSize = (DWORD)(sizeof(hdr) + GlobalSize(hDIB));
	pBmpBuf = new char[FileSize];

	memcpy(pBmpBuf, &hdr, sizeof(hdr));
	memcpy(pBmpBuf + sizeof(hdr), lpbi, GlobalSize(hDIB));

	//--------------------- 실제 파일에 기록함 --------------------------*
	FILE *pFile = NULL;

	TCHAR *tmp = filename.GetBuffer(0);

	_tfopen_s(&pFile, tmp, _T("wb"));

	bool bResult = false;
	if (pFile != NULL)
	{
		fwrite(pBmpBuf, FileSize, 1, pFile);
		fclose(pFile);
		bResult = true;
	}

	delete[] pBmpBuf;

	if (hDIB)
		GlobalFree(hDIB);

	SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);

	filename.ReleaseBuffer(0);
	return bResult;
}

void CSelfInteriorView::OnFileSave()
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CFileDialog ins_dlg(0, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
		OFN_NOCHANGEDIR, _T("All Files (*.*)|*.*|BMP Files (*.bmp)|*.bmp|"), NULL);

	// 파일 형식 콤보박스에 나열된 필터들 중에서 2번째 항목(*.txt)을 선택한다.
	ins_dlg.m_ofn.nFilterIndex = 2;

	// 다이얼로그를 띄운다.
	if (ins_dlg.DoModal() == IDOK) {
		SaveBMP(&dc, rect, 24, ins_dlg.GetPathName());
	}
}

void CSelfInteriorView::OnEditUndo()
{
	// TODO: Add your command handler code here
	if (m_listShape.GetCount() > 0) {
		m_listShape_bak.AddTail(m_listShape.GetTail());
		m_listShape.RemoveTail();
		Invalidate(FALSE);
	}
}

void CSelfInteriorView::OnEditRedo()
{
	// TODO: Add your command handler code here
	if (m_listShape_bak.GetCount() > 0) {
		m_listShape.AddTail(m_listShape_bak.GetTail());
		m_listShape_bak.RemoveTail();
		Invalidate(FALSE);
	}
}
	



void CSelfInteriorView::OnHelpHelp()
{
	// TODO: Add your command handler code here
	CHelpDlg ViewHelp;
	ViewHelp.DoModal();

}
