#pragma once
class CRectangle
{
public:
	int startX;
	int startY;
	int endX;
	int endY;

	CRectangle();
	CRectangle(CPoint m_Point);

	operator int()
	{
		return startX, startY, endX, endY;
	}
};