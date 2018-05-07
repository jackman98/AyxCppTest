#ifndef POLYGON_H
#define POLYGON_H
#include "spatial.h"
#include <a.out.h>
#include <vector>
#include <initializer_list>

namespace AyxCppTest {

class Polygon : public Area
{
	std::vector<Point> points;
	bool LineIntersection(Point line1Pt1, Point line1Pt2, Point line2Pt1, Point line2Pt2, Point &r_Out);

public:
	Polygon(std::initializer_list<Point> l);
	bool Contains(const Point &pt) override;
	~Polygon() {}

};

}

#endif // POLYGON_H
