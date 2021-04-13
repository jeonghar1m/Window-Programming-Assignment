#include "pch.h"
#include "Rectangle.h"

CRectangle::CRectangle()
{
}

CRectangle::CRectangle(CPoint m_Point)
{
	startX = m_Point.x;
	startY = m_Point.y;	
	
	endX = m_Point.x;
	endY = m_Point.y;
}