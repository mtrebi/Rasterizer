#ifndef __VECTOR_2D__
#define __VECTOR_2D__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Matrix.h"

class Normal;
class Point2D;

//----------------------------------------- class Vector2D

class Vector2D {
	public:
	
		double	x, y;

	public:
	
		Vector2D(void);											// default constructor
		Vector2D(double a);										// constructor
		Vector2D(double _x, double _y);				// constructor
		Vector2D(const Vector2D& v);							// copy constructor
		Vector2D(const Normal& n);								// constructs a vector from a Normal
		Vector2D(const Point2D& p);								// constructs a vector from a point

		~Vector2D (void);										// destructor

		Vector2D& 												// assignment operator
		operator= (const Vector2D& rhs);
		
		Vector2D& 												// assign a Normal to a vector
		operator= (const Normal& rhs); 
		
		Vector2D& 												// assign a Point2D to a vector
		operator= (const Point2D& rhs); 
		
		Vector2D												// unary minus
		operator- (void) const;									
				
		double													// length
		length(void);
		
		double													// square of the length
		len_squared(void);
		
		Vector2D												// multiplication by a double on the right
		operator* (const double a) const;
				
		Vector2D												// division by a double
		operator/ (const double a) const;
		
		Vector2D												// addition
		operator+ (const Vector2D& v) const;
		
		Vector2D& 												// compound addition
		operator+= (const Vector2D& v);					
		
		Vector2D												// subtraction
		operator- (const Vector2D& v) const;					
		
		double 													// dot product							
		operator* (const Vector2D& b) const;
		
		Vector2D 												// cross product				
		operator^ (const Vector2D& v) const;
		
		void 													// convert vector to a unit vector
		normalize(void); 
		
		Vector2D& 												// return a unit vector, and normalize the vector												
		hat(void);
};


// inlined member functions

// ------------------------------------------------------------------------ unary minus
// this does not change the current vector
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object

inline Vector2D 
Vector2D::operator- (void) const {
	return (Vector2D(-x, -y));    
}


// ---------------------------------------------------------------------  len_squared
// the square of the length

inline double													
Vector2D::len_squared(void) {	
	return (x * x + y * y);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Vector2D
Vector2D::operator* (const double a) const {	
	return (Vector2D(x * a, y * a));	
}

// ----------------------------------------------------------------------- operator/
// division by a double

inline Vector2D
Vector2D::operator/ (const double a) const {	
	return (Vector2D(x / a, y / a));	
}


// ----------------------------------------------------------------------- operator+
// addition

inline Vector2D
Vector2D::operator+ (const Vector2D& v) const {
	return (Vector2D(x + v.x, y + v.y));
}


// ----------------------------------------------------------------------- operator-
// subtraction

inline Vector2D
Vector2D::operator- (const Vector2D& v) const {
	return (Vector2D(x - v.x, y - v.y));
}


// ----------------------------------------------------------------------- operator*
// dot product

inline double 
Vector2D::operator* (const Vector2D& v) const {
	return (x * v.x + y * v.y);
} 


// ----------------------------------------------------------------------- operator^
// cross product

inline Vector2D 									
Vector2D::operator^ (const Vector2D& v) const {
	return (Vector2D(x * v.y - y * v.x));
}


// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vector2D& 
Vector2D::operator+= (const Vector2D& v) {
	x += v.x; y += v.y;
	return (*this);
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Vector2D 											// prototype
operator* (const double a, const Vector2D& v);

inline Vector2D 
operator* (const double a, const Vector2D& v) {
	return (Vector2D(a * v.x, a * v.y));	
}

#endif



