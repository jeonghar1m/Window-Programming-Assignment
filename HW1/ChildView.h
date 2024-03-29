﻿
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "Rectangle.h"
#include "Circle.h"

#define MAX_SHAPE_CNT 1000

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.

public:
	CChildView();

// 특성입니다.
public:
	bool m_LButtonDown;
	bool m_RButtonDown;

	CPoint m_StartPoint;
	CPoint m_EndPoint;

	CRectangle m_rectList[MAX_SHAPE_CNT];
	CCircle m_cirList[MAX_SHAPE_CNT];

	int m_click_cnt = 0;	// 클릭 개수

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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

