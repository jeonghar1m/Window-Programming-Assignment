
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "CShape.h"


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CScrollBar m_HBar;


	CList<CShape>m_shape;
	CShape mShape;

	CList<CPoint>m_point;
	CPoint mPoint;

	CShape shapePoint;
	CShape linePoint;

	bool m_LButtonDown;
	bool m_RButtonDown;

	long hMove;
	long vMove;
	int x = 0;
	int y = 0;
	int numShape = 0;
	bool isPlay = false;



	int elementNum = 0;
	int selectNum = 0;
	int scrollplayNum = 0;

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMenuSave();
	afx_msg void OnMenuLoad();
	afx_msg void OnPlayButton();
	afx_msg void OnStopButton();
	afx_msg void OnMenuDelete();
};

