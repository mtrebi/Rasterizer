// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class Vector2D

#include <math.h>    // for sqrt

#include "Vector2D.h"
#include "Point2D.h"

// ---------------------------------------------------------- default constructor

Vector2D::Vector2D(void)
	 : x(0.0), y(0.0)						
{}

// ---------------------------------------------------------- constructor

Vector2D::Vector2D(double a)
	 : x(a), y(a)						
{}

// ---------------------------------------------------------- constructor

Vector2D::Vector2D(double _x, double _y)	 
	: x(_x), y(_y)
{}

// ---------------------------------------------------------- copy constructor

Vector2D::Vector2D(const Vector2D& vector)
	: x(vector.x), y(vector.y)
{}


Vector2D::Vector2D(const Point2D& p)	 
	: x(p.x), y(p.y)
{}


// ---------------------------------------------------------- destructor

Vector2D::~Vector2D (void) {}



// ---------------------------------------------------------- assignment operator

Vector2D& 
Vector2D::operator= (const Vector2D& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y;

	return (*this);
}


// ---------------------------------------------------------- assignment operator 
// assign a point to a vector

Vector2D& 												
Vector2D::operator= (const Point2D& rhs) {
	x = rhs.x; y = rhs.y;
	return (*this);
}


// ----------------------------------------------------------  length
// length of the vector

double													
Vector2D::length(void) {
	return (sqrt(x * x + y * y));
}


// ----------------------------------------------------------  normalize
// converts the vector to a unit vector

void 													
Vector2D::normalize(void) {	
	double length = sqrt(x * x + y * y);
	x /= length; y /= length;
}


// ----------------------------------------------------------  hat
// converts the vector to a unit vector and returns the vector

Vector2D& 													
Vector2D::hat(void) {	
	double length = sqrt(x * x + y * y);
	x /= length; y /= length;
	return (*this);
} 