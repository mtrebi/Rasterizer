#ifndef __MATRIX__
#define __MATRIX__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

//----------------------------------------- class Matrix

class Matrix {
	
	public:
	
		double	m[4][4];								// elements
	
		
		Matrix(void);									// default constructor

		Matrix(const Matrix& mat);						// copy constructor
		
		~Matrix (void);									// destructor
			
		Matrix& 										// assignment operator
		operator= (const Matrix& rhs); 	
			
		Matrix 											// multiplication of two matrices
		operator* (const Matrix& mat) const;

		Matrix 											// divsion by a double
		operator/ (const double d);

		void											// set to the identity matrix
		set_identity(void);	
};

#endif



