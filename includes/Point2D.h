#ifndef __POINT_2D__
#define __POINT_2D__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// 2D points are used to store sample points

#include "Vector2D.h"

class Point2D {	
	public:
	
		double x, y;
				
	public:
	
		Point2D(void);										
		Point2D(const double arg);							
		Point2D(const double x1, const double y1);			
		Point2D(const Point2D& p); 						
		~Point2D(void);									

    Point2D& 													// assignment operator
      operator= (const Point2D& p);

    Point2D 													// unary minus
      operator- (void) const;

    Vector2D 													// vector joining two points
      operator- (const Point2D& p) const;

    Point2D 													// addition of a vector				
      operator+ (const Vector2D& v) const;

    Point2D 													// subtraction of a vector
      operator- (const Vector2D& v) const;

    Point2D 													// multiplication by a double on the right
      operator* (const double a) const;

    double														// square of distance bertween two points
      d_squared(const Point2D& p) const;

    double														// distance bewteen two points
      distance(const Point2D& p) const;
};


// inlined member functions

// -------------------------------------------------------------- operator-
// unary minus

inline Point2D
Point2D::operator- (void) const {
  return (Point2D(-x, -y));
}


// -------------------------------------------------------------- operator-
// the vector that joins two points

inline Vector2D
Point2D::operator- (const Point2D& p) const {
  return (Vector2D(x - p.x, y - p.y));
}


// -------------------------------------------------------------- operator+
// addition of a vector to a point that returns a new point

inline Point2D
Point2D::operator+ (const Vector2D& v) const {
  return (Point2D(x + v.x, y + v.y));
}


// -------------------------------------------------------------- operator-
// subtraction of a vector from a point that returns a new point

inline Point2D
Point2D::operator- (const Vector2D& v) const {
  return (Point2D(x - v.x, y - v.y));
}


// -------------------------------------------------------------- operator*
// mutliplication by a double on the right

inline Point2D
Point2D::operator* (const double a) const {
  return (Point2D(x * a, y * a));
}


// -------------------------------------------------------------- d_squared
// the square of the distance between the two points as a member function

inline double
Point2D::d_squared(const Point2D& p) const {
  return ((x - p.x) * (x - p.x)
    + (y - p.y) * (y - p.y));
}




// inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a double on the left

Point2D												// prototype
operator* (double a, const Point2D& p);

inline Point2D
operator* (double a, const Point2D& p) {
  return (Point2D(a * p.x, a * p.y));
}

#endif
