#pragma once
class CCircle
{
public:
	int startX;
	int startY;
	int endX;
	int endY;

	CCircle();
	CCircle(CPoint m_Point);

	operator int()
	{
		return startX, startY, endX, endY;
	}
};