#include "polygon.h"
#include <iostream>
#include <algorithm>

namespace AyxCppTest {

bool Polygon::LineIntersection(Point line1Pt1, Point line1Pt2, Point line2Pt1, Point line2Pt2, Point &r_Out)
{
	double s1_x = line1Pt2.m_x - line1Pt1.m_x;
	double s1_y = line1Pt2.m_y - line1Pt1.m_y;
	double s2_x = line2Pt2.m_x - line2Pt1.m_x;
	double s2_y = line2Pt2.m_y - line2Pt1.m_y;

	double s, t;
	s = (-s1_y * (line1Pt1.m_x - line2Pt1.m_x) + s1_x * (line1Pt1.m_y - line2Pt1.m_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (line1Pt1.m_y - line2Pt1.m_y) - s2_y * (line1Pt1.m_x - line2Pt1.m_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		r_Out.m_x = line1Pt1.m_x + (t * s1_x);
		r_Out.m_y = line1Pt1.m_y + (t * s1_y);

		return true;
	}

	return false; // No collision
}

Polygon::Polygon(std::initializer_list<Point> l)
{
	points.insert(points.end(), l.begin(), l.end());
}

bool Polygon::Contains(const Point &pt)
{
	int count = 0;
	Point temp(-500, -500);
	std::vector<Point> tempPoints;
	for (int i = 0; i < points.size() - 1; ++i) {
		if (LineIntersection(points[i], points[i + 1], pt, Point {pt.m_x, 500}, temp)) {
			if ((std::find_if(points.begin(), points.end(), [&temp](Point &p) {return p.m_x == temp.m_x && p.m_y == temp.m_y; })) == points.end()
			&& (std::find_if(tempPoints.begin(), tempPoints.end(), [&temp](Point &p) {return p.m_x == temp.m_x && p.m_y == temp.m_y; })) == tempPoints.end()) {
				++count;
				tempPoints.push_back(temp);
			}
			else if (LineIntersection(points[i], points[i + 1], pt, Point {500, pt.m_y}, temp)) {
				if ((std::find_if(points.begin(), points.end(), [&temp](Point &p) {return p.m_x == temp.m_x && p.m_y == temp.m_y; })) == points.end()
				&& (std::find_if(tempPoints.begin(), tempPoints.end(), [&temp](Point &p) {return p.m_x == temp.m_x && p.m_y == temp.m_y; })) == tempPoints.end()) {
					++count;
					tempPoints.push_back(temp);
				}
			}
		}
	}

	return (count % 2 == 0 ? false : true);
}

}
