// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class Matrix

#include "Matrix.h"

// ----------------------------------------------------------------------- default constructor
// a default matrix is an identity matrix

Matrix::Matrix(void) {	
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}


// ----------------------------------------------------------------------- copy constructor

Matrix::Matrix (const Matrix& mat) {
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = mat.m[x][y];	
}


// ----------------------------------------------------------------------- destructor

Matrix::~Matrix (void) {}   


// ----------------------------------------------------------------------- assignment operator

Matrix& 
Matrix::operator= (const Matrix& rhs) {
	if (this == &rhs)
		return (*this);

	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = rhs.m[x][y];	

	return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication of two matrices

Matrix 
Matrix::operator* (const Matrix& mat) const {
	Matrix 	product;
	
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
				sum += m[x][j] * mat.m[j][y];
 
			product.m[x][y] = sum;			
		}
	
	return (product);
}


// ----------------------------------------------------------------------- operator/
// division by a double

Matrix 
Matrix::operator/ (const double d) {
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = m[x][y] / d;	

	return (*this);
}



// ----------------------------------------------------------------------- set_identity
// set matrix to the identity matrix

void											
Matrix::set_identity(void) {
    for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}







