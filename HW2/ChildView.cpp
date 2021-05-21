
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
	m_color = RGB(0, 0, 0);
	m_shape = 0;	// 0: Rect, 1: Circle
	m_shapeCnt = 0;
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
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_COMMAND(ID_SELECT_CIRCLE, &CChildView::OnSelectCircle)
	ON_COMMAND(ID_SELECT_RECTANGLE, &CChildView::OnSelectRectangle)
	ON_UPDATE_COMMAND_UI(ID_SELECT_CIRCLE, &CChildView::OnUpdateSelectCircle)
	ON_UPDATE_COMMAND_UI(ID_SELECT_RECTANGLE, &CChildView::OnUpdateSelectRectangle)
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

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.Rectangle(-10, -10, rect.Width() + 10, rect.Height() + 10);	//하얀색 배경 화면 출력

	CBrush brush(m_color);
	memDC.SelectObject(&brush);

	CString str;

	POSITION curPos = m_pt.GetHeadPosition();
	while (curPos != NULL)
	{
		CPoint pt = m_pt.GetAt(curPos);

		if (m_shape == 0)
			memDC.Rectangle(pt.x, pt.y, pt.x + 10, pt.y + 10);	// memDC로 했을 때 도형이 출력 안되는 문제 발생.
		else if (m_shape == 1)
			dc.Ellipse(pt.x, pt.y, pt.x + 10, pt.y + 10);

		m_pt.GetNext(curPos);
	}

	str.Format(_T("Number of objects: %d"), m_shapeCnt);
	dc.TextOut(100, 100, str);

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
		m_shapeCnt++;
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

		CPoint pt = m_pt.GetNext(curPos);

		if (m_st.x < pt.x && pt.x < m_ed.x && m_st.y < pt.y && pt.y < m_ed.y)
			m_pt.RemoveAt(svPos);

	}

	Invalidate();

	CWnd::OnRButtonUp(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 255, 0);
	Invalidate();
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 0, 0);
	Invalidate();
}


void CChildView::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_color == RGB(255, 0, 0));
}


void CChildView::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_color == RGB(0, 255, 0));
}


void CChildView::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_color == RGB(0, 0, 255));
}


void CChildView::OnUpdateColorBlack(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_color == RGB(0, 0, 0));
}

void CChildView::OnSelectCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_shape = 1;

	Invalidate();
}


void CChildView::OnSelectRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_shape = 0;

	Invalidate();
}


void CChildView::OnUpdateSelectCircle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_shape == 1);
}


void CChildView::OnUpdateSelectRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_shape == 0);
}
