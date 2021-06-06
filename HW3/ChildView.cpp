
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "HW3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_SAVE, &CChildView::OnMenuSave)
	ON_COMMAND(ID_MENU_LOAD, &CChildView::OnMenuLoad)
	ON_COMMAND(ID_PLAY_BUTTON, &CChildView::OnPlayButton)
	ON_COMMAND(ID_STOP_BUTTON, &CChildView::OnStopButton)
	ON_COMMAND(ID_MENU_DELETE, &CChildView::OnMenuDelete)
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
	CClientDC dc(this);

	CRect rect;
	GetClientRect(rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.Rectangle(-10, -10, rect.Width() + 10, rect.Height() + 10);	//하얀색 배경 화면 출력

	CPen red_pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen black_pen(PS_SOLID, 1, RGB(0, 0, 0));

	POSITION pt = m_shape.GetHeadPosition();

	while (pt != NULL)
	{
		CShape mShape = m_shape.GetAt(pt);
		m_shape.GetNext(pt);

		if (mShape.num == selectNum)
			memDC.SelectObject(&red_pen);
		else
			memDC.SelectObject(&black_pen);

		if (!isPlay)
		{
			if(m_LButtonDown)
				memDC.Rectangle(mShape.pos.x - 40, mShape.pos.y - 40, mShape.pos.x + 40, mShape.pos.y + 40);
			if(m_RButtonDown)
				memDC.Ellipse(mShape.pos.x - 40, mShape.pos.y - 40, mShape.pos.x + 40, mShape.pos.y + 40);
		}
	}

	POSITION pt1 = m_point.GetHeadPosition();

	CPen dotPen;
	dotPen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen solidPen;
	solidPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	while (pt1 != NULL)
	{
		CPoint shapePoint = m_point.GetAt(pt1);
		m_point.GetNext(pt1);
		if (pt1 == NULL)
			break;
		CPoint linePoint = m_point.GetAt(pt1);

		if (isPlay)
			memDC.SelectObject(&dotPen);
		else
			memDC.SelectObject(&solidPen);

		memDC.MoveTo(shapePoint);
		memDC.LineTo(linePoint);
	}

	POSITION pt2 = m_shape.GetHeadPosition();

	if (isPlay)
	{
		if (x < numShape)
		{
			for (int i = 0; i < x; i++)
			{
				shapePoint = m_shape.GetAt(pt2);
				m_point.GetNext(pt2);
				linePoint = m_shape.GetAt(pt2);
			}

			hMove = (linePoint.pos.x - shapePoint.pos.x);
			vMove = (linePoint.pos.x - shapePoint.pos.y);
			memDC.SelectObject(&solidPen);

			if(m_LButtonDown)
				memDC.Rectangle(shapePoint.pos.x - 40 + hMove * y, shapePoint.pos.y - 40 + vMove * y, shapePoint.pos.x + 40 + hMove * y, shapePoint.pos.y + 40 + vMove * y);
			if(m_RButtonDown)
				memDC.Ellipse(shapePoint.pos.x - 40 + hMove * y, shapePoint.pos.y - 40 + vMove * y, shapePoint.pos.x + 40 + hMove * y, shapePoint.pos.y + 40 + vMove * y);

			m_HBar.SetScrollPos(scrollplayNum);
		}

		if (x >= numShape)
		{
			x = 1;
			scrollplayNum = 0;
		}
	}

	m_HBar.SetScrollRange(0, elementNum - 1);

	m_HBar.ShowWindow(true);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!isPlay)
	{
		m_LButtonDown = true;
		mShape.pos = point;
		mShape.num = elementNum;
		m_shape.AddTail(mShape);
		m_point.AddHead(mShape.pos);
		numShape++;
		elementNum++;
		Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!isPlay)
	{
		m_RButtonDown = true;
		mShape.pos = point;
		mShape.num = elementNum;
		m_shape.AddTail(mShape);
		m_point.AddHead(mShape.pos);
		numShape++;
		elementNum++;
		Invalidate();
	}
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnRButtonUp(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_HBar.Create(SBS_HORZ, CRect(0, 0, 400, 20), this, 101);

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CChildView::OnMenuSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file(_T("save.dat"), CFile::modeCreate | CFile::modeWrite);

	file.Write(&elementNum, sizeof(elementNum));
}


void CChildView::OnMenuLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file(_T("data.dat"), CFile::modeRead);

	m_shape.RemoveAll();
	m_point.RemoveAll();
	file.Read(&elementNum, sizeof(elementNum));

	selectNum = 0;
	Invalidate();
}

void CChildView::OnMenuDelete()
{
	m_shape.RemoveAll();
	m_point.RemoveAll();
	m_HBar.SetScrollPos(0);
	elementNum = 0;
	Invalidate();
}

void CChildView::OnPlayButton()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	isPlay = true;
}


void CChildView::OnStopButton()
{
	scrollplayNum = 0, x = 0, y = 0;
	isPlay = false;
	Invalidate();
}