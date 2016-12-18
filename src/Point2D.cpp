// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Point2D.h"

// ------------------------------------------------ default constructor

Point2D::Point2D(void)
	: x(0.0), y(0.0)
{}


// ------------------------------------------------ constructor

Point2D::Point2D(const float arg)
	: x(arg), y(arg)
{}


// ------------------------------------------------ constructor

Point2D::Point2D(const float x1, const float y1)
	: x(x1), y(y1)
{}


// ------------------------------------------------ copy constructor

Point2D::Point2D(const Point2D& p)
	: x(p.x), y(p.y)
{}


// ------------------------------------------------ destructor

Point2D::~Point2D(void) {}


// ------------------------------------------------ assignment operator

Point2D& 							
Point2D::operator= (const Point2D& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x;
	y = rhs.y;

	return (*this);
}
