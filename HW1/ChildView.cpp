
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "HW1.h"
#include "ChildView.h"
#include "Rectangle.h"
#include "Circle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int shapeCnt = 0;

// CChildView

CChildView::CChildView()
{
	m_LButtonDown = false;
	m_RButtonDown = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.Rectangle(-10, -10, rect.Width() + 10, rect.Height() + 10);	//하얀색 배경 화면 출력

	if (m_LButtonDown)
	{
		bitmap.LoadBitmap(IDB_BITMAP1);	// Error: 솔루션 구성을 Release가 아닌 Debug로 설정하면 프로그램이 터져버리는 문제 발생.
		CBrush brush(&bitmap);
		memDC.SelectObject(&brush);
		memDC.Rectangle(m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y);
		//memDC.Rectangle(m_rectList[shapeCnt].startX, m_rectList[shapeCnt].startY, m_rectList[shapeCnt].endX, m_rectList[shapeCnt].endY);
		shapeCnt++;
	}

	if (m_RButtonDown)
	{
		CBrush brush(RGB(0, 0, 255));
		memDC.SelectObject(&brush);
		memDC.Ellipse(m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y);
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPaintDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);


	m_LButtonDown = true;
	m_StartPoint = point;

	m_rectList[shapeCnt] = CRectangle(point);

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_RButtonDown = true;
	m_StartPoint = point;


	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_LButtonDown = false;
	m_EndPoint = point;

	m_rectList[shapeCnt] = CRectangle(point);

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_RButtonDown = false;
	m_EndPoint = point;

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_LButtonDown || m_RButtonDown)
	{
		m_EndPoint = point;
		Invalidate();
	}	
	//if (m_LButtonDown)
	//{
	//	m_rectList[shapeCnt] = point;
	//	Invalidate();
	//}

	//if (m_RButtonDown)
	//{
	//	m_EndPoint = point;
	//	Invalidate();
	//}

	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}