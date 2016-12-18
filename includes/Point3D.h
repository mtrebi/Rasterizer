#ifndef __POINT3D__
#define __POINT3D__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Matrix.h"
#include "Vector3D.h"

class Point3D {
	public:
	
		double x, y, z;
	
		Point3D();													// default constructor
		Point3D(const double a);									// constructor
		Point3D(const double a, const double b, const double c);	// constructor
		Point3D(const Point3D& p);									// copy constructor
		~Point3D();													// destructor
		
		Point3D& 													// assignment operator
		operator= (const Point3D& p);
		
		Point3D 													// unary minus
		operator- (void) const;
	
		Vector3D 													// vector joining two points
		operator- (const Point3D& p) const;
		
		Point3D 													// addition of a vector				
		operator+ (const Vector3D& v) const;
		
		Point3D 													// subtraction of a vector
		operator- (const Vector3D& v) const;
				
		Point3D 													// multiplication by a double on the right
		operator* (const double a) const;
		
		double														// square of distance bertween two points
		d_squared(const Point3D& p) const;
		
		double														// distance bewteen two points
		distance(const Point3D& p) const;
};



// inlined member functions

// -------------------------------------------------------------- operator-
// unary minus

inline Point3D 
Point3D::operator- (void) const {
	return (Point3D(-x, -y, -z));
}


// -------------------------------------------------------------- operator-
// the vector that joins two points

inline Vector3D 
Point3D::operator- (const Point3D& p) const {
	return (Vector3D(x - p.x,y - p.y,z - p.z));
}


// -------------------------------------------------------------- operator+
// addition of a vector to a point that returns a new point

inline Point3D 
Point3D::operator+ (const Vector3D& v) const {
	return (Point3D(x + v.x, y + v.y, z + v.z));
}


// -------------------------------------------------------------- operator-
// subtraction of a vector from a point that returns a new point

inline Point3D 
Point3D::operator- (const Vector3D& v) const {
	return (Point3D(x - v.x, y - v.y, z - v.z));
}


// -------------------------------------------------------------- operator*
// mutliplication by a double on the right

inline Point3D 
Point3D::operator* (const double a) const {
	return (Point3D(x * a,y * a,z * a));
}


// -------------------------------------------------------------- d_squared
// the square of the distance between the two points as a member function

inline double
Point3D::d_squared(const Point3D& p) const {
	return (	(x - p.x) * (x - p.x) 
			+ 	(y - p.y) * (y - p.y)
			+	(z - p.z) * (z - p.z) );
}




// inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a double on the left

Point3D												// prototype
operator* (double a, const Point3D& p);

inline Point3D
operator* (double a, const Point3D& p) {
	return (Point3D(a * p.x, a * p.y, a * p.z));
}



// non-inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Point3D 											// prototype					
operator* (const Matrix& mat, const Point3D& p);

#endif

