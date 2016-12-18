// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the definition of the class Point3D

#include <math.h>
#include "Point3D.h"


// --------------------------------------------- default constructor

Point3D::Point3D()
	:x(0), y(0), z(0)
{}


// --------------------------------------------- constructor

Point3D::Point3D(const double a)
	:x(a), y(a), z(a)
{}

// --------------------------------------------- constructor

Point3D::Point3D(const double a, const double b, const double c)
	:x(a), y(b), z(c)
{}


// --------------------------------------------- copy constructor

Point3D::Point3D(const Point3D& p)
	:x(p.x), y(p.y), z(p.z)
{}


// --------------------------------------------- destructor

Point3D::~Point3D() 
{}


// --------------------------------------------- assignment operator

Point3D& 
Point3D::operator= (const Point3D& rhs) {
	
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}



// --------------------------------------------- distance
// distance between two points

double
Point3D::distance(const Point3D& p) const {
	return (sqrt(		(x - p.x) * (x - p.x) 
					+ 	(y - p.y) * (y - p.y)
					+	(z - p.z) * (z - p.z) ));
}


// non-member function

// --------------------------------------------- operator*
// multiplication by a matrix on the left

Point3D 						
operator* (const Matrix& mat, const Point3D& p) {
	return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
					mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
					mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}


