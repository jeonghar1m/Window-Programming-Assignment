
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "HW2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_RButton = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);

	dc.SelectStockObject(BLACK_BRUSH);

	POSITION curPos = m_pt.GetHeadPosition();
	while (curPos != NULL)
	{
		CPoint pt = m_pt.GetAt(curPos);
		//CPoint pt = m_pt.GetNext(curPos);
		//dc.SetPixelV(pt, RGB(0, 0, 0));
		dc.Rectangle(pt.x, pt.y, pt.x + 10, pt.y + 10);
		m_pt.GetNext(curPos);
	}

	dc.SelectStockObject(DC_BRUSH);
	if (m_RButton)
		dc.Rectangle(m_st.x, m_st.y, m_ed.x, m_ed.y);
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON)
	{
		m_pt.AddTail(point);
		Invalidate();
	}
	else if (nFlags & MK_RBUTTON)
	{
		m_ed = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_st = point;
	m_ed = point;
	m_RButton = true;

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_ed = point;
	m_RButton = false;

	POSITION curPos = m_pt.GetHeadPosition();
	while (curPos != NULL)
	{
		POSITION svPos = curPos;

		//CPoint pt = m_pt.GetAt(curPos);

		CPoint pt = m_pt.GetNext(curPos);

		if (m_st.x < pt.x && pt.x < m_ed.x && m_st.y < pt.y && pt.y < m_ed.y)
			m_pt.RemoveAt(svPos);
	}

	Invalidate();

	CWnd::OnRButtonUp(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CWnd::OnEraseBkgnd(pDC);
	//return true;
}
