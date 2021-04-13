#include "pch.h"
#include "Circle.h"

CCircle::CCircle()
{
}

CCircle::CCircle(CPoint m_Point)
{
	startX = m_Point.x;
	startY = m_Point.y;

	endX = m_Point.x;
	endY = m_Point.y;
}